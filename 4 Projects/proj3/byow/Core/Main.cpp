#include "Engine.hpp"
int main(int argc, char **argv) {
    if (argc > 3) {
        std::cerr << "Can only have two arguments - the flag and input string\n";
        return 1;
    }
    Engine engine;
    if (argc == 3 && std::string(argv[1]) == "-s")
        std::cout << TETile::toString(engine.interactWithInputString(argv[2]));
    else if (argc == 3 && std::string(argv[1]) == "-p")
        std::cout << "Coming soon.\n";
    else
        engine.interactWithKeyboard();
}
