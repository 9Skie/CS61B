#pragma once
#include "BeeCountingStage.hpp"
class AdventureGame {
    Stage currentStage;
    Stage parseResponse(const std::string &response) {
        if (response.empty())
            return nullptr;
        auto &responses = currentStage->getResponses();
        auto it = responses.find(course::lower(response));
        if (it != responses.end())
            return it->second;
        for (const auto &[key, value] : responses)
            if (course::lower(key).find(course::lower(response)) != std::string::npos)
                return value;
        return nullptr;
    }

  public:
    std::istream &in;
    explicit AdventureGame(std::istream &input)
        : AdventureGame(input,
                        std::make_shared<FillerStage>(
                            "It's a wonderful day of learning about computer science! We are going "
                            "to see so many cool things today!\nLet's go! (To answer the prompts, "
                            "type the possibilities in the brackets to go to that choice)\"\n",
                            Responses{{"go", std::make_shared<BeeCountingStage>(input)}})) {}
    AdventureGame(std::istream &input, Stage first) : currentStage(first), in(input) {}
    void handleStage() {
        currentStage->playStage();
        std::cout << toString() << '\n';
        if (currentStage->getResponses().empty()) {
            currentStage.reset();
            return;
        }
        Stage next;
        while (!(next = parseResponse(course::readLine(in))))
            std::cout << "Sorry, I don't understand that. Please type one of the responses in the "
                         "brackets!\n";
        currentStage = next;
    }
    void play() {
        while (currentStage)
            handleStage();
        std::cout << "All in another fun day of learning computer science :)\n";
    }
    std::string toString() const {
        std::string result = currentStage->nextStagePrompt() + "\n";
        auto &responses = currentStage->getResponses();
        if (!responses.empty()) {
            result += ">>";
            for (const auto &[key, value] : responses)
                result += " [" + key + "]";
        }
        return result;
    }
};
