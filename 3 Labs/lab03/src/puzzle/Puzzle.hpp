#pragma once
#include "Support.hpp"
// Do not modify this file. Use your debugger and edit answer.txt.
class Puzzle {
    inline static const std::vector<std::string> LOTS_OF_STRINGS{
        "According", "to",   "all", "known",  "laws", "of",     "aviation,", "there",
        "is",        "no",   "way", "a",      "bee",  "should", "be",        "able",
        "to",        "fly.", "Its", "wings",  "are",  "too",    "small",     "to",
        "get",       "its",  "fat", "little", "body", "off",    "the",       "ground."};
    static bool isCorrect(int answer) {
        return course::stringHash(std::to_string(answer)) == -32772622;
    }
    static void erroringMethod(course::Random &r) {
        std::string s;
        std::cout << "Hmm, what is the value of `guessThis` when the out-of-bounds exception is "
                     "thrown?\nReplace the first line of `answer.txt` accordingly.\nHint: Use an "
                     "exception breakpoint.\n";
        while (r.nextInt(100) != 10) {
            guessThis = course::add32(guessThis, r.nextInt());
            s = LOTS_OF_STRINGS.at(r.nextInt(LOTS_OF_STRINGS.size() + 1));
        }
    }

  public:
    inline static int guessThis = 0;
    static int loadAnswer(const std::string &file) {
        std::ifstream in(file);
        if (!in)
            throw std::runtime_error("Cannot read " + file);
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream tokens(line);
            std::string token;
            if (tokens >> token && course::isInt(token))
                return course::parseInt(token);
        }
        throw std::runtime_error("Could not find answer in " + file);
    }
    static int puzzle() {
        int answer = loadAnswer("src/puzzle/answer.txt");
        if (isCorrect(answer)) {
            std::cout << "That's correct! Nice work!\n";
            return answer;
        }
        course::Random r(1678971254);
        for (int i = 0; i < 1323; ++i)
            if (r.nextInt() == -2034104197)
                erroringMethod(r);
        return 0;
    }
};
