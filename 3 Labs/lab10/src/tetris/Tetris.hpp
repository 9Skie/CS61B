#pragma once
#include "BagRandomizer.hpp"
#include "Movement.hpp"
#include "Tetromino.hpp"
#include "tileengine/Tileset.hpp"
#include "tileengine/TERenderer.hpp"
// Tetris assignment by Erik Nelson, Omar Yu, Noah Adhikari and Jasmine Lin.
class Tetris {
    static constexpr int WIDTH = 10, HEIGHT = 20, GAME_HEIGHT = 25;
    World board, auxiliary;
    Movement movement;
    bool gameOver = false;
    std::shared_ptr<Tetromino> currentTetromino;
    int score = 0;
    TERenderer ter;
    course::Random random;
    BagRandomizer bagRandom;
    std::vector<Tetromino> pieces = Tetromino::values();
    int64_t prevActionTimestamp = 0, prevFrameTimestamp = 0;
    bool auxFilled = false;
    bool isGameOver() const {
        return gameOver;
    }
    void renderBoard() {
        ter.drawTiles(board);
        renderScore();
        Draw::show();
        if (auxFilled)
            auxToBoard();
        else
            fillBoard(Tileset::NOTHING);
    }
    void spawnPiece() {
        if (board[4][19] != Tileset::NOTHING)
            gameOver = true;
        currentTetromino = std::make_shared<Tetromino>(pieces[bagRandom.getValue()]);
        currentTetromino->reset();
    }
    void updateBoard() {
        auto t = getCurrentTetromino();
        if (actionDeltaTime() > 1000) {
            movement.dropDown();
            resetActionTimer();
            Tetromino::draw(*t, board, t->pos.x, t->pos.y);
            return;
        }
        // TODO: Handle keystrokes to move and rotate the piece using Movement helpers.
        Tetromino::draw(*t, board, t->pos.x, t->pos.y);
    }
    void incrementScore(int linesCleared) { /* TODO: Apply the scoring rules. */ }
    void renderScore() { /* TODO: Draw the score using Draw. */ }
    void fillBoard(const TETile &tile) {
        for (auto &column : board)
            std::fill(column.begin(), column.end(), tile);
    }
    static void copyArray(const World &src, World &dest) {
        dest = src;
    }
    void auxToBoard() {
        copyArray(auxiliary, board);
    }
    int64_t actionDeltaTime() const {
        return course::millis() - prevActionTimestamp;
    }
    void resetActionTimer() {
        prevActionTimestamp = course::millis();
    }

  public:
    explicit Tetris(int64_t seed = course::Random().nextLong(), bool display = true)
        : board(WIDTH, std::vector<TETile>(GAME_HEIGHT)), auxiliary(board),
          movement(WIDTH, GAME_HEIGHT, *this), random(seed), bagRandom(random, 7) {
        if (display)
            ter.initialize(WIDTH, HEIGHT);
        fillBoard(Tileset::NOTHING);
        fillAux();
    }
    void clearLines(World &tiles) {
        int linesCleared = 0;
        // TODO: Find and clear completed rows, including cascading effects.
        // TODO: Increment the score based on linesCleared.
        fillAux();
    }
    void runGame() {
        resetActionTimer();
        // TODO: Run the game loop until gameOver or Draw::isOpen() becomes false.
        // Use the helper methods described in the assignment.
    }
    World &getBoard() {
        return board;
    }
    int getScore() const {
        return score;
    }
    World &getAuxiliary() {
        return auxiliary;
    }
    std::shared_ptr<Tetromino> getCurrentTetromino() {
        if (!currentTetromino)
            throw std::logic_error("Spawn a piece before moving it");
        return currentTetromino;
    }
    void setCurrentTetromino() {
        currentTetromino.reset();
    }
    void setAuxTrue() {
        auxFilled = true;
    }
    void fillAux() {
        copyArray(board, auxiliary);
    }
};
