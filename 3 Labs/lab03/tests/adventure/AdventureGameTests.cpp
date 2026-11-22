#define TEST_MAIN
#include "Test.hpp"
#include "adventure/AdventureGame.hpp"
template <class T> void checkStage(const std::string &name) {
    std::ifstream in("tests/data/" + name + "/input.txt");
    CHECK(in.good());
    course::random.setSeed(1337);
    test::Capture capture(std::cout);
    AdventureGame game(in, std::make_shared<T>(in));
    game.handleStage();
    auto normalize = [](std::string s) {
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        return course::trim(s);
    };
    CHECK(normalize(capture.str()) ==
          normalize(course::readFile("tests/data/" + name + "/answers.txt")));
}
TEST(bee) {
    checkStage<BeeCountingStage>("BeeCountingStage");
}
TEST(species) {
    checkStage<SpeciesListStage>("SpeciesListStage");
}
TEST(palindrome) {
    checkStage<PalindromeStage>("PalindromeStage");
}
TEST(machine) {
    checkStage<MachineStage>("MachineStage");
}
