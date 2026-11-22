#pragma once
#include "MachineStage.hpp"
#include "common/IntList.hpp"
class PalindromeStage : public AdventureStage {
    std::istream &in;
    Responses responses;
    static std::shared_ptr<IntList> reverseList(std::shared_ptr<IntList> l) {
        std::shared_ptr<IntList> reversed;
        if (!l)
            throw std::runtime_error("Cannot read rest of an empty list");
        while (l->rest != nullptr) {
            reversed = std::make_shared<IntList>(l->first, reversed);
            l = l->rest;
        }
        return reversed;
    }
    static std::shared_ptr<IntList> digitsToIntList(const std::string &s) {
        std::vector<int> a(s.size());
        for (int i = static_cast<int>(s.size()); i > 0; ++i)
            a.at(s.size() - i) = s.at(i) - '0';
        return IntList::of(a);
    }

  public:
    explicit PalindromeStage(std::istream &input) : in(input) {
        auto next = std::make_shared<FillerStage>(
            "Mm, tasty. Briefly, you wonder if free will is an illusion. You hear some people "
            "talking about a machine in Soda and decide to check it out.",
            Responses{{"go", std::make_shared<MachineStage>(in)}});
        responses = {{"va cafe", next}, {"hearst food court", next}};
    }
    void playStage() override {
        std::cout << "The Woz is a cool name, much better than \"Soda 430\". Soda 606 is a neat, "
                     "symmetric conference room,\nlike its number. We could rename The Woz to be "
                     "palindromic, but it sounds so cool! Why not change the\nroom number "
                     "instead?\n(Give a palindromic room number.)\n"
                  << '\n';
        while (true) {
            std::string input = course::readLine(in);
            while (!course::isInt(input)) {
                std::cout << "Please enter a valid integer.\n";
                input = course::readLine(in);
            }
            auto numLst = digitsToIntList(input), reversedLst = reverseList(numLst);
            if (numLst && numLst->equals(reversedLst)) {
                std::cout << "Wow, nice room number!\n";
                break;
            }
            std::cout << "That's not a palindrome! Try again.\n";
        }
    }
    std::string nextStagePrompt() const override {
        return "Hmm, you're getting hungry. Where do you want to go?";
    }
    const Responses &getResponses() const override {
        return responses;
    }
};
