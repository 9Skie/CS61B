#pragma once
#include "tileengine/TETile.hpp"
// Piece definitions and movement helpers by Erik Nelson, Omar Yu and Noah Adhikari.
class Tetromino {
    TETile tile;
    static std::vector<std::vector<bool>> ijToXY(const std::vector<std::vector<bool>> &a) {
        std::vector<std::vector<bool>> result(a.at(0).size(), std::vector<bool>(a.size()));
        for (size_t x = 0; x < result.size(); ++x)
            for (size_t y = 0; y < a.size(); ++y)
                result[x][y] = a[a.size() - y - 1][x];
        return result;
    }

  public:
    std::vector<std::vector<bool>> shape;
    int width, height;
    struct Point {
        int x, y;
    } pos{3, 20};
    Tetromino(Color color, const std::vector<std::vector<bool>> &s)
        : tile("█", color, Color::BLACK, "", 0), shape(ijToXY(s)), width(shape.at(0).size()),
          height(shape.size()) {}
    static std::vector<Tetromino> values() {
        return {Tetromino(Color::hex(0x31e7ef), {{false, false, false, false},
                                                 {true, true, true, true},
                                                 {false, false, false, false},
                                                 {false, false, false, false}}),
                Tetromino(Color::hex(0x5a65ad),
                          {
                              {true, false, false},
                              {true, true, true},
                              {false, false, false},
                          }),
                Tetromino(Color::hex(0xef7921),
                          {
                              {false, false, true},
                              {true, true, true},
                              {false, false, false},
                          }),
                Tetromino(Color::hex(0xf7d308),
                          {
                              {true, true},
                              {true, true},
                          }),
                Tetromino(Color::hex(0x42b642),
                          {{false, true, true}, {true, true, false}, {false, false, false}}),
                Tetromino(Color::hex(0xad4d9c),
                          {
                              {false, true, false},
                              {true, true, true},
                              {false, false, false},
                          }),
                Tetromino(Color::hex(0xef2029),
                          {{true, true, false}, {false, true, true}, {false, false, false}})};
    }
    static void draw(const Tetromino &t, World &board, int bx, int by) {
        for (int x = 0; x < t.width; ++x)
            for (int y = 0; y < t.height; ++y)
                if (t.shape.at(x).at(y))
                    board.at(bx + x).at(by + y) = t.tile;
    }
    void reset() {
        pos = {3, 20};
    }
};
