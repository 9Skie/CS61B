#include "MemoryGame.hpp"
int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Please enter a seed\n";
        return 1;
    }
    MemoryGame game(40, 40, std::stoll(argv[1]));
    game.startGame();
}
