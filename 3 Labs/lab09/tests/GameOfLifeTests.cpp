#define TEST_MAIN
#include "Test.hpp"
#include "gameoflife/GameOfLife.hpp"
static void checkIfPatternFilesAreModified();
static int hashFile(std::string, std::string);
static std::string newlineReplacer(std::string);

const std::string SAVE_FILE = "src/save.txt";
const std::string SAVE_TEST = "tests/testFiles/saveTest.txt";
const std::string LOAD_TEST = "tests/testFiles/loadTest.txt";

const std::string BLANK = "patterns/blank.txt";
const std::string GLIDERGUN = "patterns/glidergun.txt";
const std::string HAMMERHEAD = "patterns/hammerhead.txt";
const std::string PENTADECATHLON = "patterns/pentadecathlon.txt";

/**
 * Compares the two states, if orientation is aligned.
 * @param student
 * @param expected
 */
static void checkState(World student, World expected) {
    CHECK(student.size() == expected.size());
    for (size_t x = 0; x < student.size(); ++x)
        CHECK(student[x].size() == expected[x].size());
    for (size_t i = 0; i < student.size(); i++) {
        for (size_t j = 0; j < student[0].size(); j++) {
            CHECK(student[i][j].description() == expected[i][j].description());
        }
    }
}

/**
 * Checks for the state of the world before and after a single generation,
 * with dimensions of 3 by 3.
 */
TEST(oneGeneration) {
    checkIfPatternFilesAreModified();
    World testInput = World{{Tileset::CELL, Tileset::CELL, Tileset::NOTHING},
                            {Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING},
                            {Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING}};

    World result = World{{Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING},
                         {Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING},
                         {Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING}};

    GameOfLife student(testInput, true);

    // Generate next state from the provided input.
    World nextState = student.nextGeneration(testInput);

    // Height and width need to stay the same before and after the generation.
    CHECK(testInput.size() == nextState.size());
    CHECK(testInput[0].size() == nextState[0].size());

    // Check that the next generation state is as expected.
    checkState(nextState, result);
}

/**
 * Checks the state of the world after multiple generations.
 */
TEST(multipleGenerations) {
    checkIfPatternFilesAreModified();
    World testInput = World{{Tileset::CELL, Tileset::CELL, Tileset::CELL, Tileset::CELL},
                            {Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING, Tileset::CELL},
                            {Tileset::NOTHING, Tileset::CELL, Tileset::NOTHING, Tileset::CELL},
                            {Tileset::NOTHING, Tileset::CELL, Tileset::NOTHING, Tileset::CELL}};
    GameOfLife student(testInput, true);
    // Generate next state from the provided input.
    World firstState = student.nextGeneration(testInput);

    /**
     * 4 4
     * 0111
     * 1001
     * 0001
     * 0000
     */
    World generationOne =
        World{{Tileset::NOTHING, Tileset::CELL, Tileset::CELL, Tileset::CELL},
              {Tileset::CELL, Tileset::NOTHING, Tileset::NOTHING, Tileset::CELL},
              {Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING, Tileset::CELL},
              {Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING}};
    checkState(firstState, generationOne);

    /**
     * 4 4
     * 0111
     * 0101
     * 0000
     * 0000
     */
    World secondState = student.nextGeneration(firstState);
    World generationTwo =
        World{{Tileset::NOTHING, Tileset::CELL, Tileset::CELL, Tileset::CELL},
              {Tileset::NOTHING, Tileset::CELL, Tileset::NOTHING, Tileset::CELL},
              {Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING},
              {Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING}};
    checkState(secondState, generationTwo);

    /**
     * 4 4
     * 0101
     * 0101
     * 0000
     * 0000
     */
    World thirdState = student.nextGeneration(secondState);
    World generationThree =
        World{{Tileset::NOTHING, Tileset::CELL, Tileset::NOTHING, Tileset::CELL},
              {Tileset::NOTHING, Tileset::CELL, Tileset::NOTHING, Tileset::CELL},
              {Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING},
              {Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING}};
    checkState(thirdState, generationThree);
}

/**
 * Check for the save format, without generation of the next state, using a random seed
 * as the initial state.
 * @throws IOException
 */
TEST(onlySave) {
    checkIfPatternFilesAreModified();
    /**
     * Should expect the board to be saved like in the following (not including dimensions):
     * 010
     * 011
     * 100
     * 010
     */
    World result = World{{Tileset::NOTHING, Tileset::CELL, Tileset::NOTHING},
                         {Tileset::NOTHING, Tileset::CELL, Tileset::CELL},
                         {Tileset::CELL, Tileset::NOTHING, Tileset::NOTHING},
                         {Tileset::NOTHING, Tileset::CELL, Tileset::NOTHING}};

    GameOfLife student(result, true);
    student.saveBoard();

    std::string f1 = newlineReplacer(course::readFile(SAVE_FILE));
    std::string f2 = newlineReplacer(course::readFile(SAVE_TEST));

    CHECK(f1 == f2);
}

/**
 * Check that loading works and matches expected output.
 * @throws IOException
 */
TEST(onlyLoad) {
    checkIfPatternFilesAreModified();
    GameOfLife student(1234567, true);

    World result = World{{Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING},
                         {Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING},
                         {Tileset::NOTHING, Tileset::NOTHING, Tileset::NOTHING}};
    World loadResult = student.loadBoard(LOAD_TEST);
    checkState(loadResult, result);
}

/**
 * This checks if any of the pattern files have been modified. Modifications include
 * adding a newline, deleting/replacing characters, adding characters, etc.
 * DO NOT MODIFY ANYTHING IN THE FILE (otherwise testing will be harder).
 */
static void checkIfPatternFilesAreModified() {
    if (hashFile("boba", BLANK) % 404 != -172) {
        throw test::Failure(
            "blank.txt has been modified, please restore it back to the original version");
    }
    if (hashFile("panda express", GLIDERGUN) % 404 != -92) {
        throw test::Failure(
            "glidergun.txt has been modified, please restore it back to the original version");
    }
    if (hashFile("rickroll", HAMMERHEAD) % 404 != -252) {
        throw test::Failure(
            "hammerhead.txt has been modified, please restore it back to the original version");
    }
    if (hashFile("brrrrrr", PENTADECATHLON) % 404 != 380) {
        throw test::Failure(
            "pentadecathlon.txt has been modified. Please restore it to the original version.");
    }
    if (hashFile("stop", SAVE_TEST) % 404 != 262) {
        throw test::Failure(
            "saveTest.txt has been modified. Please restore it to the original version.");
    }
    if (hashFile("watch", LOAD_TEST) % 404 != -75) {
        throw test::Failure(
            "loadTest.txt has been modified. Please restore it to the original version.");
    }
}

static std::string newlineReplacer(std::string s) {
    s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
    return s;
}

static int hashFile(std::string delimiter, std::string file) {
    std::istringstream in(course::readFile(file));
    std::string line, joined;
    bool first = true;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (!first)
            joined += delimiter;
        joined += line;
        first = false;
    }
    return course::stringHash(joined);
}
