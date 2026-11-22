#pragma once
#include "Support.hpp"
#include <cstddef>

struct Color {
    int r, g, b;
    Color(int red = 0, int green = 0, int blue = 0) : r(red), g(green), b(blue) {}
    static Color hex(unsigned rgb) {
        return {int(rgb >> 16 & 255), int(rgb >> 8 & 255), int(rgb & 255)};
    }
    bool operator==(const Color &c) const {
        return r == c.r && g == c.g && b == c.b;
    }
    static const Color BLACK, WHITE, RED, GREEN, BLUE, DARK_GRAY, GRAY, MAGENTA, PINK, ORANGE,
        YELLOW;
};
inline const Color Color::BLACK{0, 0, 0}, Color::WHITE{255, 255, 255}, Color::RED{255, 0, 0},
    Color::GREEN{0, 255, 0}, Color::BLUE{0, 0, 255}, Color::DARK_GRAY{64, 64, 64},
    Color::GRAY{128, 128, 128}, Color::MAGENTA{255, 0, 255}, Color::PINK{255, 175, 175},
    Color::ORANGE{255, 200, 0}, Color::YELLOW{255, 255, 0};

// Small SDL3/FreeType drawing API. Coordinates start at the bottom left.
// All drawing and input calls belong on the main thread.
namespace Draw {
void setCanvasSize(int width, int height);
void setXscale(double low, double high);
void setYscale(double low, double high);
void setFont(int pixelSize);
void setPenColor(Color color);
void clear(Color color = Color::WHITE);
void filledRectangle(double x, double y, double halfWidth, double halfHeight);
void filledSquare(double x, double y, double halfSize);
void line(double x0, double y0, double x1, double y1);
void text(double x, double y, const std::string &value);
void textLeft(double x, double y, const std::string &value);
void textRight(double x, double y, const std::string &value);
void picture(double x, double y, const std::string &path);
void save(const std::string &path);
std::vector<unsigned char> png();
void displayPng(const std::vector<unsigned char> &bytes);
void show();
void enableDoubleBuffering();
void pause(int milliseconds);
bool isOpen();
bool hasNextKeyTyped();
char nextKeyTyped();
bool isKeyPressed(char key);
double mouseX();
double mouseY();
bool isMousePressed();
void waitUntilClosed();
void close();
} // namespace Draw
