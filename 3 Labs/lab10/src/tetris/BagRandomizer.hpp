#pragma once
#include "Support.hpp"
// Seven-bag randomizer by Erik Nelson.
class BagRandomizer {
    course::Random &random;
    std::vector<int> values;
    int capacity;
    void refillValues() {
        values.clear();
        for (int i = 0; i < capacity; ++i)
            values.push_back(i);
    }

  public:
    BagRandomizer(course::Random &r, int n) : random(r), capacity(n) {
        if (n <= 0)
            throw std::invalid_argument("Empty bag");
        refillValues();
    }
    int getValue() {
        if (values.empty())
            refillValues();
        int i = random.nextInt(values.size());
        int value = values[i];
        values.erase(values.begin() + i);
        return value;
    }
};
