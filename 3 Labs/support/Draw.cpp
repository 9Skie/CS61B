#include "Draw.hpp"
#include <SDL3/SDL.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <png.h>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <filesystem>
#include <tuple>

namespace {
struct State {
    SDL_Window *window = nullptr;
    SDL_Surface *canvas = nullptr;
    FT_Library library = nullptr;
    FT_Face face = nullptr;
    int width = 512, height = 512, fontSize = 14;
    double xmin = 0, xmax = 1, ymin = 0, ymax = 1;
    Color pen = Color::BLACK;
    bool open = true;
    std::deque<char> keys;
    ~State() {
        if (face)
            FT_Done_Face(face);
        if (library)
            FT_Done_FreeType(library);
        if (canvas)
            SDL_DestroySurface(canvas);
        if (window)
            SDL_DestroyWindow(window);
        SDL_Quit();
    }
};
State &state() {
    static State s;
    return s;
}
void ensure() {
    if (!state().window)
        Draw::setCanvasSize(512, 512);
}
int px(double x) {
    auto &s = state();
    return int(std::lround((x - s.xmin) * s.width / (s.xmax - s.xmin)));
}
int py(double y) {
    auto &s = state();
    return int(std::lround((s.ymax - y) * s.height / (s.ymax - s.ymin)));
}
void poll() {
    if (!state().window)
        return;
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
            state().open = false;
        if (e.type == SDL_EVENT_TEXT_INPUT)
            for (char c : std::string(e.text.text))
                state().keys.push_back(c);
        if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_BACKSPACE)
            state().keys.push_back('\b');
        if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_RETURN)
            state().keys.push_back('\n');
    }
}
void pixel(int x, int y, Color color, unsigned alpha = 255) {
    auto &s = state();
    if (x < 0 || y < 0 || x >= s.width || y >= s.height)
        return;
    auto *p = static_cast<unsigned char *>(s.canvas->pixels) + y * s.canvas->pitch + x * 4;
    p[0] = (color.r * alpha + p[0] * (255 - alpha)) / 255;
    p[1] = (color.g * alpha + p[1] * (255 - alpha)) / 255;
    p[2] = (color.b * alpha + p[2] * (255 - alpha)) / 255;
    p[3] = 255;
}
void font() {
    auto &s = state();
    if (!s.library && FT_Init_FreeType(&s.library))
        throw std::runtime_error("Cannot initialize FreeType");
    if (s.face)
        return;
    std::vector<std::string> paths;
    if (auto *path = std::getenv("CS61B_FONT"))
        paths.emplace_back(path);
    paths.insert(paths.end(), {"/System/Library/Fonts/Supplemental/Arial Unicode.ttf",
                               "/System/Library/Fonts/Monaco.ttf",
                               "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
                               "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"});
    for (const auto &path : paths)
        if (std::filesystem::exists(path) && !FT_New_Face(s.library, path.c_str(), 0, &s.face))
            break;
    if (!s.face)
        throw std::runtime_error("No font found. Set CS61B_FONT to a Unicode .ttf font.");
}
std::vector<uint32_t> codepoints(const std::string &text) {
    std::vector<uint32_t> out;
    for (size_t i = 0; i < text.size();) {
        uint32_t c = static_cast<unsigned char>(text[i++]);
        int extra = 0;
        if (c >= 0xf0) {
            c &= 7;
            extra = 3;
        } else if (c >= 0xe0) {
            c &= 15;
            extra = 2;
        } else if (c >= 0xc0) {
            c &= 31;
            extra = 1;
        }
        while (extra-- && i < text.size())
            c = (c << 6) | (static_cast<unsigned char>(text[i++]) & 63);
        out.push_back(c);
    }
    return out;
}
struct Glyph {
    int width, height, left, top, advance;
    std::vector<unsigned char> pixels;
};
const Glyph &glyph(uint32_t c) {
    auto &s = state();
    font();
    static std::map<std::pair<int, uint32_t>, Glyph> cache;
    auto key = std::make_pair(s.fontSize, c);
    auto it = cache.find(key);
    if (it != cache.end())
        return it->second;
    FT_Set_Pixel_Sizes(s.face, 0, s.fontSize);
    if (FT_Load_Char(s.face, c, FT_LOAD_RENDER | FT_LOAD_NO_BITMAP))
        throw std::runtime_error("Cannot render glyph");
    auto g = s.face->glyph;
    Glyph result{int(g->bitmap.width), int(g->bitmap.rows),    g->bitmap_left,
                 g->bitmap_top,        int(g->advance.x >> 6), {}};
    result.pixels.resize(result.width * result.height);
    for (int y = 0; y < result.height; ++y) {
        int stride = std::abs(g->bitmap.pitch);
        const auto *row =
            g->bitmap.buffer + (g->bitmap.pitch >= 0 ? y : result.height - 1 - y) * stride;
        for (int x = 0; x < result.width; ++x) {
            if (g->bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
                result.pixels[y * result.width + x] = (row[x / 8] & (0x80 >> (x % 8))) ? 255 : 0;
            else if (g->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY)
                result.pixels[y * result.width + x] = row[x];
            else
                throw std::runtime_error("Unsupported font bitmap format");
        }
    }
    return cache.emplace(key, std::move(result)).first->second;
}
void drawText(double x, double y, const std::string &text, int alignment) {
    ensure();
    auto chars = codepoints(text);
    int width = 0;
    for (auto c : chars)
        width += glyph(c).advance;
    int left = px(x) - (alignment == 0 ? width / 2 : alignment == 1 ? 0 : width);
    int baseline = py(y) + state().fontSize / 3;
    for (auto c : chars) {
        const auto &g = glyph(c);
        for (int row = 0; row < g.height; ++row)
            for (int col = 0; col < g.width; ++col)
                pixel(left + g.left + col, baseline - g.top + row, state().pen,
                      g.pixels[row * g.width + col]);
        left += g.advance;
    }
}
struct PngImage {
    png_image image{};
    PngImage() {
        image.version = PNG_IMAGE_VERSION;
    }
    ~PngImage() {
        png_image_free(&image);
    }
};
void blitPng(png_image &img, int x, int y) {
    img.format = PNG_FORMAT_RGBA;
    std::vector<unsigned char> bytes(PNG_IMAGE_SIZE(img));
    if (!png_image_finish_read(&img, nullptr, bytes.data(), 0, nullptr))
        throw std::runtime_error(img.message);
    for (unsigned row = 0; row < img.height; ++row)
        for (unsigned col = 0; col < img.width; ++col) {
            auto *p = &bytes[(row * img.width + col) * 4];
            pixel(x + col, y + row, Color(p[0], p[1], p[2]), p[3]);
        }
}
} // namespace
namespace Draw {
void setCanvasSize(int width, int height) {
    if (width <= 0 || height <= 0 || width > 16384 || height > 16384)
        throw std::invalid_argument("Invalid canvas dimensions");
    auto &s = state();
    if (!s.window) {
        if (!SDL_Init(SDL_INIT_VIDEO))
            throw std::runtime_error(SDL_GetError());
        s.window = SDL_CreateWindow("CS61B C++", width, height, 0);
        if (!s.window)
            throw std::runtime_error(SDL_GetError());
        SDL_StartTextInput(s.window);
    } else
        SDL_SetWindowSize(s.window, width, height);
    if (s.canvas)
        SDL_DestroySurface(s.canvas);
    s.canvas = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA32);
    if (!s.canvas)
        throw std::runtime_error(SDL_GetError());
    s.width = width;
    s.height = height;
    s.open = true;
    clear(Color::BLACK);
}
void setXscale(double low, double high) {
    if (!(low < high))
        throw std::invalid_argument("Invalid x scale");
    state().xmin = low;
    state().xmax = high;
}
void setYscale(double low, double high) {
    if (!(low < high))
        throw std::invalid_argument("Invalid y scale");
    state().ymin = low;
    state().ymax = high;
}
void setFont(int size) {
    if (size <= 0)
        throw std::invalid_argument("Invalid font size");
    state().fontSize = size;
}
void setPenColor(Color c) {
    state().pen = c;
}
void clear(Color c) {
    ensure();
    SDL_FillSurfaceRect(state().canvas, nullptr,
                        SDL_MapSurfaceRGBA(state().canvas, c.r, c.g, c.b, 255));
}
void filledRectangle(double x, double y, double hw, double hh) {
    ensure();
    SDL_Rect r{px(x - hw), py(y + hh), px(x + hw) - px(x - hw), py(y - hh) - py(y + hh)};
    auto c = state().pen;
    SDL_FillSurfaceRect(state().canvas, &r, SDL_MapSurfaceRGBA(state().canvas, c.r, c.g, c.b, 255));
}
void filledSquare(double x, double y, double h) {
    filledRectangle(x, y, h, h);
}
void line(double x0, double y0, double x1, double y1) {
    ensure();
    int x = px(x0), y = py(y0), ex = px(x1), ey = py(y1), dx = std::abs(ex - x),
        dy = -std::abs(ey - y), sx = x < ex ? 1 : -1, sy = y < ey ? 1 : -1, err = dx + dy;
    while (true) {
        pixel(x, y, state().pen);
        if (x == ex && y == ey)
            break;
        int e = 2 * err;
        if (e >= dy) {
            err += dy;
            x += sx;
        }
        if (e <= dx) {
            err += dx;
            y += sy;
        }
    }
}
void text(double x, double y, const std::string &s) {
    drawText(x, y, s, 0);
}
void textLeft(double x, double y, const std::string &s) {
    drawText(x, y, s, 1);
}
void textRight(double x, double y, const std::string &s) {
    drawText(x, y, s, 2);
}
void picture(double x, double y, const std::string &path) {
    ensure();
    PngImage p;
    if (!png_image_begin_read_from_file(&p.image, path.c_str()))
        throw std::invalid_argument("Cannot load PNG: " + path);
    blitPng(p.image, px(x) - p.image.width / 2, py(y) - p.image.height / 2);
}
std::vector<unsigned char> png() {
    ensure();
    PngImage p;
    p.image.width = state().width;
    p.image.height = state().height;
    p.image.format = PNG_FORMAT_RGBA;
    png_alloc_size_t size = 0;
    if (!png_image_write_to_memory(&p.image, nullptr, &size, 0, state().canvas->pixels,
                                   state().canvas->pitch, nullptr))
        throw std::runtime_error(p.image.message);
    std::vector<unsigned char> bytes(size);
    if (!png_image_write_to_memory(&p.image, bytes.data(), &size, 0, state().canvas->pixels,
                                   state().canvas->pitch, nullptr))
        throw std::runtime_error(p.image.message);
    bytes.resize(size);
    return bytes;
}
void save(const std::string &path) {
    auto bytes = png();
    course::writeFile(path, std::string(bytes.begin(), bytes.end()));
}
void displayPng(const std::vector<unsigned char> &bytes) {
    ensure();
    PngImage p;
    if (!png_image_begin_read_from_memory(&p.image, bytes.data(), bytes.size()))
        throw std::runtime_error("Invalid PNG frame");
    if (p.image.width != unsigned(state().width) || p.image.height != unsigned(state().height))
        throw std::runtime_error("Frame dimensions do not match canvas");
    blitPng(p.image, 0, 0);
    show();
}
void show() {
    ensure();
    poll();
    if (!state().open)
        return;
    auto *target = SDL_GetWindowSurface(state().window);
    if (!target || !SDL_BlitSurface(state().canvas, nullptr, target, nullptr) ||
        !SDL_UpdateWindowSurface(state().window))
        throw std::runtime_error(SDL_GetError());
}
void enableDoubleBuffering() {} // The offscreen surface is always buffered.
void pause(int milliseconds) {
    auto end = course::millis() + milliseconds;
    do {
        poll();
        SDL_Delay(1);
    } while (state().open && course::millis() < end);
}
bool isOpen() {
    poll();
    return state().open;
}
bool hasNextKeyTyped() {
    poll();
    return !state().keys.empty();
}
char nextKeyTyped() {
    if (!hasNextKeyTyped())
        throw std::out_of_range("No typed key");
    char c = state().keys.front();
    state().keys.pop_front();
    return c;
}
bool isKeyPressed(char key) {
    poll();
    return SDL_GetKeyboardState(
        nullptr)[SDL_GetScancodeFromKey(std::tolower(static_cast<unsigned char>(key)), nullptr)];
}
double mouseX() {
    poll();
    float x;
    SDL_GetMouseState(&x, nullptr);
    auto &s = state();
    return s.xmin + x * (s.xmax - s.xmin) / s.width;
}
double mouseY() {
    poll();
    float y;
    SDL_GetMouseState(nullptr, &y);
    auto &s = state();
    return s.ymax - y * (s.ymax - s.ymin) / s.height;
}
bool isMousePressed() {
    poll();
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK;
}
void waitUntilClosed() {
    while (isOpen())
        pause(16);
}
void close() {
    state().open = false;
}
} // namespace Draw
