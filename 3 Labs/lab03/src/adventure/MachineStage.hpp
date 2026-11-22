#pragma once
#include "FillerStage.hpp"
class MachineStage : public AdventureStage {
    std::istream &in;
    Responses responses;

  public:
    explicit MachineStage(std::istream &input)
        : in(input),
          responses{
              {"li ka shing", std::make_shared<FillerStage>(
                                  "You head to Li Ka Shing 245, and sit in your favorite seat.")},
              {"zoom", std::make_shared<FillerStage>(
                           "You find an open seat, set up your laptop, and join the Zoom.")}} {}
    std::string nextStagePrompt() const override {
        return "It's almost time for lecture! How are you attending?";
    }
    const Responses &getResponses() const override {
        return responses;
    }
    void playStage() override {
        std::cout << "On the first (zeroth?) floor of Soda, below the labs, you find a mysterious "
                     "machine.\nIt has holes for two lists of ints of the same length, and a third "
                     "hole that looks\nlike it would output a number. The label reads:\n\n    "
                     "'SumOfElementWiseMax-inator'\n\n... Huh. You decide to experiment with the "
                     "machine for a bit.\n"
                  << '\n';
        while (true) {
            std::cout << "Enter a sequence of ints, separated by commas:\n";
            auto listOne = course::split(course::readLine(in), "[\\s,]+");
            std::cout << "Enter a second sequence, with the same number of ints:\n";
            auto listTwo = course::split(course::readLine(in), "[\\s,]+");
            if (listOne.size() != listTwo.size()) {
                std::cout << "The provided lists aren't of the same length!\n";
                continue;
            }
            std::vector<int> arrOne(listOne.size()), arrTwo(listTwo.size());
            bool valid = true;
            for (size_t i = 0; i < listOne.size(); ++i) {
                if (!course::isInt(listOne[i]) || !course::isInt(listTwo[i])) {
                    std::cout << "Hmm, are you sure you typed a sequence of integers?\n";
                    valid = false;
                    break;
                }
                arrOne[i] = course::parseInt(listOne[i]);
                arrTwo[i] = course::parseInt(listTwo[i]);
            }
            if (!valid)
                continue;
            int result = sumOfElementwiseMax(arrOne, arrTwo);
            std::cout << "The machine whirrs briefly before outputting a slip of paper, reading "
                      << result << '\n';
            std::cout << "Does that seem right to you?\nEnter [y] if you want to move on, and "
                         "anything else to try again.\n";
            if (course::lower(course::readLine(in)) == "y") {
                std::cout << "Satisfied with your tinkering, you leave the machine behind.\n";
                break;
            }
        }
    }
    static int mysteryMax(int a, int b) {
        int difference = course::signed32(uint32_t(b) - uint32_t(a));
        int w = difference < 0 ? -1 : 0;
        int z = difference < 0 ? 0 : -1;
        return (b & w) | (a & z);
    }
    static int mysteryAdd(int a, int b) {
        uint32_t carry = uint32_t(a) & uint32_t(b), bits = uint32_t(a) ^ uint32_t(b);
        while (carry != 0) {
            carry <<= 1;
            uint32_t temp = bits ^ carry;
            carry &= bits;
            bits = temp;
        }
        return course::signed32(bits);
    }
    // Returns a new array whose entry i is the max of a[i] and b[i].
    static std::vector<int> arrayMax(const std::vector<int> &a, const std::vector<int> &b) {
        if (a.size() != b.size()) {
            std::cout << "ERROR! Array lengths don't match\n";
            return {};
        }
        std::vector<int> result(a.size());
        for (size_t i = 0; i < a.size(); ++i)
            result[i] = mysteryMax(a[i], b[i]);
        return result;
    }
    // Returns the sum of all elements in x.
    static int arraySum(const std::vector<int> &x) {
        int sum = 0;
        for (size_t i = 0; i < x.size(); ++i)
            sum = course::add32(sum, mysteryAdd(sum, x[i]));
        return sum;
    }
    static int sumOfElementwiseMax(const std::vector<int> &a, const std::vector<int> &b) {
        return arraySum(arrayMax(a, b));
    }
};
