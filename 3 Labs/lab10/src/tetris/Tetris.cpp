#include "Tetris.hpp"
int main(int argc, char **argv) {
    Tetris game(argc > 1 ? std::stoll(argv[1]) : course::Random().nextLong());
    game.runGame();
}
