#pragma once
#include "InputSource.hpp"
#include "Support.hpp"
class RandomInputSource : public InputSource {
    course::Random r;

  public:
    explicit RandomInputSource(int64_t seed) : r(seed) {}
    char getNextKey() override {
        return char(r.nextInt(26) + 'A');
    }
    bool possibleNextInput() override {
        return true;
    }
};
