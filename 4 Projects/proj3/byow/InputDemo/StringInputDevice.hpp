#pragma once
#include "InputSource.hpp"
#include <string>
class StringInputDevice : public InputSource {
    std::string input;
    size_t index = 0;

  public:
    explicit StringInputDevice(std::string s) : input(s) {}
    char getNextKey() override {
        return input.at(index++);
    }
    bool possibleNextInput() override {
        return index < input.size();
    }
};
