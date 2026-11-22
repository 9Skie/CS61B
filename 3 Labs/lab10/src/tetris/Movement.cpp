#include "Tetris.hpp"
void Movement::tryMove(int dx, int dy) {
    auto t = tetris.getCurrentTetromino();
    if (canMove(dx, dy)) {
        t->pos.x += dx;
        t->pos.y += dy;
    } else if (dy < 0) {
        Tetromino::draw(*t, tetris.getBoard(), t->pos.x, t->pos.y);
        tetris.fillAux();
        tetris.setAuxTrue();
        tetris.setCurrentTetromino();
    }
}
bool Movement::canMove(int dx, int dy) {
    auto t = tetris.getCurrentTetromino();
    for (int x = 0; x < t->width; ++x)
        for (int y = 0; y < t->height; ++y)
            if (t->shape[x][y]) {
                int bx = t->pos.x + x + dx, by = t->pos.y + y + dy;
                if (bx < 0 || bx >= WIDTH || by < 0 || by >= GAME_HEIGHT ||
                    tetris.getBoard()[bx][by] != Tileset::NOTHING)
                    return false;
            }
    return true;
}
void Movement::dropDown() {
    tryMove(0, -1);
}
bool Movement::canRotate(const std::vector<std::vector<bool>> &shape) {
    auto t = tetris.getCurrentTetromino();
    auto &board = tetris.getAuxiliary();
    for (size_t x = 0; x < shape.size(); ++x)
        for (size_t y = 0; y < shape[x].size(); ++y)
            if (shape[x][y]) {
                int bx = t->pos.x + int(x), by = t->pos.y + int(y);
                if (bx < 0 || by < 0 || bx >= int(board.size()) || by >= int(board[0].size()) ||
                    board[bx][by] != Tileset::NOTHING)
                    return false;
            }
    return true;
}
void Movement::rotate(Rotation direction) {
    auto t = tetris.getCurrentTetromino();
    int h = t->shape.size(), w = t->shape[0].size();
    std::vector<std::vector<bool>> shape(h, std::vector<bool>(w));
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
            shape[i][j] =
                direction == Rotation::LEFT ? t->shape[j][h - i - 1] : t->shape[w - j - 1][i];
    if (canRotate(shape)) {
        t->shape = shape;
        t->height = shape[0].size();
        t->width = shape.size();
    }
}
