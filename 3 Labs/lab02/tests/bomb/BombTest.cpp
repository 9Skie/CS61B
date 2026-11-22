#define TEST_MAIN
#include "Test.hpp"
#include "bomb/BombMain.hpp"
static void checkPhase(int phase, int hash) {
    test::Capture output(std::cerr);
    BombMain::answers(phase);
    std::string line = output.str(),
                marker = "phase " + std::to_string(phase) + " with the password \"";
    auto start = line.find(marker);
    CHECK(start != std::string::npos);
    start += marker.size();
    auto end = line.find('"', start);
    CHECK(end != std::string::npos);
    CHECK(course::stringHash(line.substr(start, end - start)) == hash);
}
TEST(phase0) {
    checkPhase(0, -777276206);
}
TEST(phase1) {
    checkPhase(1, 1729584786);
}
TEST(phase2) {
    checkPhase(2, 1097364068);
}

TEST(sourceUnchanged) {
    std::istringstream in(course::readFile("src/bomb/Bomb.hpp"));
    std::string line, joined;
    bool first = true;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (!first)
            joined += "cheese";
        joined += line;
        first = false;
    }
    CHECK(course::stringHash(joined) == -1304885217);
}
