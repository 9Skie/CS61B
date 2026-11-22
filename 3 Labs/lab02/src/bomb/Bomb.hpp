#pragma once
#include "common/IntList.hpp"
#include <unordered_set>
class Bomb {
  public:
    // DO NOT MODIFY THIS FILE. Find the passwords with your debugger.
    std::string shufflePassword(const std::string &s) {
        std::string code = std::to_string(course::stringHash(s));
        course::random.setSeed(1337);
        course::random.shuffle(code);
        return code;
    }
    std::shared_ptr<IntList> shufflePasswordIntList(const std::string &s) {
        std::string code = std::to_string(course::stringHash(s));
        course::random.setSeed(61833);
        course::random.shuffle(code);
        std::shared_ptr<IntList> curr;
        for (int i = static_cast<int>(code.size()) - 1; i >= 0; --i)
            curr = std::make_shared<IntList>(code[i] - '0', curr);
        return curr;
    }
    void phase0(const std::string &password) {
        if (password != shufflePassword("hello")) {
            std::cout << "Phase 0 went BOOM!\n";
            return;
        }
        std::cerr << "You passed phase 0 with the password \"" << password << "\"\n";
    }
    void phase1(const std::shared_ptr<IntList> &password) {
        if (!shufflePasswordIntList("bye")->equals(password)) {
            std::cout << "Phase 1 went BOOM!\n";
            return;
        }
        std::cerr << "You passed phase 1 with the password \"" << password->print() << "\"\n";
    }
    void phase2(const std::string &password) {
        course::Random r(1337);
        std::unordered_set<int> seen;
        // Explicit buckets give this puzzle the same iteration order on every platform.
        std::vector<std::vector<int>> numbers(262144);
        while (seen.size() < 100000) {
            int value = r.nextInt();
            if (seen.insert(value).second) {
                uint32_t hash = uint32_t(value) ^ (uint32_t(value) >> 16);
                numbers[hash & (numbers.size() - 1)].push_back(value);
            }
        }
        bool correct = false;
        int i = 0;
        for (const auto &bucket : numbers)
            for (int number : bucket) {
                if (i == 1337 && course::parseInt(password) == number)
                    correct = true;
                ++i;
            }
        if (!correct) {
            std::cout << "Phase 2 went BOOM!\n";
            return;
        }
        std::cerr << "You passed phase 2 with the password \"" << password << "\"\n";
    }
};
