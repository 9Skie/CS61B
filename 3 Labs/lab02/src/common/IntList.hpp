#pragma once
#include "Support.hpp"
struct IntList {
    int first;
    std::shared_ptr<IntList> rest;
    IntList(int f, std::shared_ptr<IntList> r = nullptr) : first(f), rest(r) {}
    int get(int i) const {
        if (i == 0)
            return first;
        if (!rest || i < 0)
            throw std::out_of_range("IntList index");
        return rest->get(i - 1);
    }
    static std::shared_ptr<IntList> of(const std::vector<int> &values) {
        std::shared_ptr<IntList> result;
        for (auto it = values.rbegin(); it != values.rend(); ++it)
            result = std::make_shared<IntList>(*it, result);
        return result;
    }
    bool equals(const std::shared_ptr<IntList> &other) const {
        if (!other || first != other->first)
            return false;
        return rest ? rest->equals(other->rest) : !other->rest;
    }
    std::string print() const {
        return std::to_string(first) + (rest ? " -> " + rest->print() : "");
    }
};
