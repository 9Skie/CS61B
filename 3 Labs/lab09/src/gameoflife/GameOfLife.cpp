#include "GameOfLife.hpp"
int main(int argc, char **argv) {
    if (argc == 3) {
        if (std::string(argv[1]) == "-l") {
            GameOfLife game{std::string(argv[2])};
            game.runGame();
        } else
            std::cerr << "Verify your program arguments!\n";
    } else {
        course::Random r;
        GameOfLife game(argc > 1 ? std::stoll(argv[1]) : r.nextLong());
        game.runGame();
    }
}
