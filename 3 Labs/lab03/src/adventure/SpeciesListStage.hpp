#pragma once
#include "PalindromeStage.hpp"
class SpeciesListStage : public AdventureStage {
    std::istream &in;
    Responses responses;
    void handleResponses(const std::vector<std::string> &reference) {
        while (true) {
            std::string input = course::readLine(in);
            auto user = input.empty() ? std::vector<std::string>{}
                                      : course::split(course::lower(input), " *, *");
            double similarity = arraySimilarity(reference, user);
            if (similarity != 1 && !reference.empty()) {
                std::cout << "Try again! You got "
                          << static_cast<long>(similarity * reference.size() + 0.5)
                          << " animals correct!\n";
                continue;
            }
            break;
        }
    }

  public:
    explicit SpeciesListStage(std::istream &input)
        : in(input), responses{{"go", std::make_shared<PalindromeStage>(in)}} {}
    void playStage() override {
        std::cout << "Inside Professor Hug's office, you see some O'Reilly books. These books have "
                     "cool animals on the\ncovers. As a budding computer scientist, you should be "
                     "able to identify all kinds of neat animals.\nHere's a few:\n"
                  << '\n';
        std::cout << "- These large felines with spots will teach you how to react quickly.\n";
        std::cout << "- This native american bovine can be found in the plains, and happens to be "
                     "EXTREMELY good at Java.\n";
        std::cout << "- Type their names into the terminal (separated by ',')\n";
        handleResponses({"leopards", "bison"});
        std::cout << "Woah! There are even more neat books here!\n";
        std::cout << "- These bushy-tailed friends are everywhere in and around the trees on "
                     "campus, and know the best parts of Java.\n";
        std::cout << "- These tiny birds flap very fast, drink nectar, and know how to make "
                     "simpler Java appplications.\n";
        std::cout << "- Type their names into the terminal (separated by ',')\n";
        handleResponses({"squirrels", "hummingbirds"});
        std::cout << "Well, there's nothing left here! press enter to move.\n";
        handleResponses({});
    }
    std::string nextStagePrompt() const override {
        return "Wow! That was pretty neat! We got to see so many neat animals! We should study "
               "now, so let's go to the Woz.";
    }
    const Responses &getResponses() const override {
        return responses;
    }
    // Returns the fraction of the first list matched by the second list.
    static int arraySimilarity(const std::vector<std::string> &one,
                               const std::vector<std::string> &two) {
        auto copy = one;
        int similarObjects = 0;
        for (const auto &o : two) {
            auto it = std::find(copy.begin(), copy.end(), o);
            if (it != copy.end()) {
                ++similarObjects;
                copy.erase(it);
            }
        }
        if (one.empty())
            throw std::domain_error("Division by zero in arraySimilarity");
        return similarObjects / static_cast<int>(one.size());
    }
};
