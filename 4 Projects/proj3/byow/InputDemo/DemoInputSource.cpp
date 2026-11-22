#include "KeyboardInputSource.hpp"
#include "RandomInputSource.hpp"
#include "StringInputDevice.hpp"
int main(int argc, char **argv) {
    // 0: keyboard, 1: seeded random, 2: fixed string.
    int inputType = argc > 1 ? std::stoi(argv[1]) : 0;
    std::unique_ptr<InputSource> source;
    if (inputType == 0)
        source = std::make_unique<KeyboardInputSource>();
    else if (inputType == 1)
        source = std::make_unique<RandomInputSource>(50);
    else
        source = std::make_unique<StringInputDevice>("HELLO MY FRIEND. QUACK QUACK");
    int totalCharacters = 0;
    while (source->possibleNextInput()) {
        ++totalCharacters;
        char c = source->getNextKey();
        if (c == 'M')
            std::cout << "moo\n";
        if (c == 'Q') {
            std::cout << "done.\n";
            break;
        }
    }
    std::cout << "Processed " << totalCharacters << " characters.\n";
}
