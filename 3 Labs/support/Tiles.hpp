#pragma once
#include "Draw.hpp"
// Tile values are copied safely; boards use x first, y second (origin bottom left).
class TETile;
using World = std::vector<std::vector<TETile>>;
class TETile {
    std::string symbol, label, filepath;
    Color foreground, background;
    int tileId = -1;

  public:
    TETile() = default;
    TETile(std::string character, Color textColor, Color backgroundColor, std::string description,
           int id = -1, std::string path = "")
        : symbol(character), label(description), filepath(path), foreground(textColor),
          background(backgroundColor), tileId(id) {}
    TETile(std::string character, Color textColor, Color backgroundColor, std::string description,
           std::string path)
        : TETile(character, textColor, backgroundColor, description, -1, path) {}
    TETile(const TETile &t, Color color) : TETile(t) {
        foreground = color;
    }
    TETile(const TETile &t, std::string character) : TETile(t) {
        symbol = character;
    }
    std::string character() const {
        return symbol;
    }
    std::string description() const {
        return label;
    }
    int id() const {
        return tileId;
    }
    bool operator==(const TETile &t) const {
        return symbol == t.symbol && label == t.label && foreground == t.foreground &&
               background == t.background && filepath == t.filepath && tileId == t.tileId;
    }
    bool operator!=(const TETile &t) const {
        return !(*this == t);
    }
    void draw(double x, double y) const {
        if (symbol.empty())
            throw std::invalid_argument("Uninitialized tile");
        if (!filepath.empty()) {
            try {
                Draw::picture(x + 0.5, y + 0.5, filepath);
                return;
            } catch (const std::invalid_argument &) {
            }
        }
        Draw::setPenColor(background);
        Draw::filledSquare(x + 0.5, y + 0.5, 0.5);
        Draw::setPenColor(foreground);
        Draw::text(x + 0.5, y + 0.5, symbol);
    }
    static TETile colorVariant(const TETile &t, int dr, int dg, int db, course::Random &r) {
        auto color = [&](int v, int d) { return std::clamp(v - d + r.nextInt(2 * d + 1), 0, 255); };
        return TETile(t, Color(color(t.foreground.r, dr), color(t.foreground.g, dg),
                               color(t.foreground.b, db)));
    }
    static std::string toString(const World &world) {
        if (world.empty())
            return "";
        std::string result;
        for (int y = int(world[0].size()) - 1; y >= 0; --y) {
            for (size_t x = 0; x < world.size(); ++x) {
                if (world.at(x).at(y).symbol.empty())
                    throw std::invalid_argument("Uninitialized tile at " + std::to_string(x) + "," +
                                                std::to_string(y));
                result += world.at(x).at(y).symbol;
            }
            result += '\n';
        }
        return result;
    }
    static World copyOf(const World &tiles) {
        return tiles;
    }
};
class TERenderer {
    int width = 0, height = 0, xOffset = 0, yOffset = 0;

  public:
    void initialize(int w, int h, int xOff = 0, int yOff = 0) {
        width = w;
        height = h;
        xOffset = xOff;
        yOffset = yOff;
        Draw::setCanvasSize(w * 16, h * 16);
        Draw::setFont(14);
        Draw::setXscale(0, w);
        Draw::setYscale(0, h);
        Draw::clear(Color::BLACK);
        Draw::enableDoubleBuffering();
        Draw::show();
    }
    void drawTiles(const World &world) {
        Draw::clear(Color::BLACK);
        for (size_t x = 0; x < world.size(); ++x)
            for (size_t y = 0; y < world[x].size(); ++y)
                world[x][y].draw(x + xOffset, y + yOffset);
    }
    void renderFrame(const World &world) {
        drawTiles(world);
        Draw::show();
    }
};
