#pragma once
#include <vector>
class Tetris;
class Movement {
    int WIDTH, GAME_HEIGHT;
    Tetris &tetris;

  public:
    enum class Rotation { RIGHT, LEFT };
    Movement(int width, int height, Tetris &game)
        : WIDTH(width), GAME_HEIGHT(height), tetris(game) {}
    void rotateRight() {
        rotate(Rotation::RIGHT);
    }
    void rotateLeft() {
        rotate(Rotation::LEFT);
    }
    void tryMove(int deltaX, int deltaY);
    bool canMove(int deltaX, int deltaY);
    void dropDown();
    bool canRotate(const std::vector<std::vector<bool>> &newShape);
    void rotate(Rotation direction);
};
