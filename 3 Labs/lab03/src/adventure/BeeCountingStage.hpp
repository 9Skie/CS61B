#pragma once
#include "SpeciesListStage.hpp"
class BeeCountingStage : public AdventureStage {
    inline static const std::vector<int> SOME_NEAT_NUMBERS{5, 3, 2, 6, 7};
    std::istream &in;
    Responses responses;
    std::optional<std::vector<std::string>> input;
    int sumInput() {
        int sum = 0;
        for (size_t i = 0; i <= input.value().size(); ++i)
            sum += course::parseInt(input.value().at(i));
        return sum;
    }

  public:
    explicit BeeCountingStage(std::istream &stream)
        : in(stream), responses{{"go", std::make_shared<SpeciesListStage>(in)}} {}
    void playStage() override {
        while (true) {
            std::cout << "In Soda 326, you can find the computers known as \"The Hive\". It is a "
                         "little-known fact that\nthey are called this because they are home to "
                         "(friendly) robotic bees. How many bees do you see?\n"
                      << '\n';
            int count = 0, expectedSum = 0;
            while (count < 3) {
                int currNum = SOME_NEAT_NUMBERS[course::random.nextInt(SOME_NEAT_NUMBERS.size())];
                for (int i = 0; i < currNum; ++i)
                    std::cout << "-.-" << (i < currNum - 1 ? " " : "");
                std::cout << '\n';
                std::string answer = course::readLine(in);
                while (!course::isInt(answer)) {
                    std::cout << "Please enter a valid integer.\n";
                    answer = course::readLine(in);
                }
                expectedSum += currNum;
                input.value().push_back(answer);
                if (count < 2)
                    std::cout << "How about now?\n";
                ++count;
            }
            if (sumInput() == expectedSum)
                break;
            std::cout << "You did not count the bees correctly. Let's try again!\n";
            input.value().clear();
        }
        std::cout << "Those sure were some bees!\n";
    }
    std::string nextStagePrompt() const override {
        return "Phew, that was a lot of counting! It's time for Professor Hug's office hours! "
               "Let's head up to his office on the 7th floor.";
    }
    const Responses &getResponses() const override {
        return responses;
    }
};
