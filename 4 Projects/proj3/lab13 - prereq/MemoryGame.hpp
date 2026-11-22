#pragma once
#include "Draw.hpp"
#include "byow/Core/RandomUtils.hpp"
class MemoryGame {
    int width, height, round = 0;
    std::optional<course::Random> rand;
    bool gameOver = false, playerTurn = false;
    inline static const std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";
    inline static const std::vector<std::string> ENCOURAGEMENT{
        "You can do this!", "I believe in you!", "You got this!",      "You're a star!",
        "Go Bears!",        "Too easy for you!", "Wow, so impressive!"};

  public:
    MemoryGame(int w, int h, int64_t seed) : width(w), height(h) {
        Draw::setCanvasSize(width * 16, height * 16);
        Draw::setFont(30);
        Draw::setXscale(0, width);
        Draw::setYscale(0, height);
        Draw::clear(Color::BLACK);
        Draw::enableDoubleBuffering();
        // TODO: Initialize the seeded random generator (rand.emplace(seed)).
    }
    std::string generateRandomString(int n) { /* TODO: Generate n random letters. */
        return "";
    }
    void drawFrame(const std::string &s) {
        // TODO: Draw s at the center of the screen.
        // TODO: Unless the game is over, show game information at the top.
    }
    void flashSequence(const std::string &letters) { /* TODO: Display letters one by one, blanking
                                                        the screen between them. */
    }
    std::string solicitNCharsInput(int n) { /* TODO: Read and display n letters from the player. */
        return "";
    }
    void startGame() {
        // TODO: Initialize game state.
        // TODO: Establish the game loop, including a window-close condition.
    }
};
