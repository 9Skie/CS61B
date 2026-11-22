#define TEST_MAIN
#include "Test.hpp"
#include "puzzle/Puzzle.hpp"
TEST(puzzle) {
    CHECK(course::stringHash(std::to_string(Puzzle::puzzle())) == -32772622);
}
TEST(sourceUnchanged) {
    auto clean = [](const std::string &text) {
        std::istringstream in(text);
        std::string line, result;
        while (std::getline(in, line)) {
            line = course::trim(line);
            if (!line.empty())
                result += line + '\n';
        }
        return result;
    };
    CHECK(clean(course::readFile("src/puzzle/Puzzle.hpp")) ==
          clean(course::readFile("tests/puzzle/PuzzleReference.txt")));
}
