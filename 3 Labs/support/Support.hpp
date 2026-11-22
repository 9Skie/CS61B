#pragma once
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace course {
// Fixed-width arithmetic keeps the supplied debugging puzzles reproducible.
inline int32_t signed32(uint32_t x) {
    return x <= 0x7fffffffU ? static_cast<int32_t>(x)
                            : static_cast<int32_t>(static_cast<int64_t>(x) - 0x100000000LL);
}
inline int32_t add32(int32_t a, int32_t b) {
    return signed32(uint32_t(a) + uint32_t(b));
}
inline int32_t stringHash(const std::string &s) {
    uint32_t h = 0;
    for (unsigned char c : s)
        h = 31 * h + c;
    return signed32(h);
}
// 48-bit linear congruential generator used by the original course fixtures.
class Random {
    uint64_t state;
    uint32_t next(int bits) {
        state = (state * 0x5deece66dULL + 11) & ((1ULL << 48) - 1);
        return static_cast<uint32_t>(state >> (48 - bits));
    }

  public:
    explicit Random(int64_t seed = std::chrono::steady_clock::now().time_since_epoch().count()) {
        setSeed(seed);
    }
    void setSeed(int64_t seed) {
        state = (uint64_t(seed) ^ 0x5deece66dULL) & ((1ULL << 48) - 1);
    }
    int32_t nextInt() {
        return signed32(next(32));
    }
    int nextInt(int bound) {
        if (bound <= 0)
            throw std::invalid_argument("bound must be positive");
        if ((bound & -bound) == bound)
            return static_cast<int>((int64_t(bound) * next(31)) >> 31);
        int bits, val;
        do {
            bits = next(31);
            val = bits % bound;
        } while (int64_t(bits) - val + bound - 1 > INT32_MAX);
        return val;
    }
    int64_t nextLong() {
        int32_t high = nextInt(), low = nextInt();
        uint64_t bits = (uint64_t(uint32_t(high)) << 32) + uint64_t(int64_t(low));
        return bits <= uint64_t(INT64_MAX) ? int64_t(bits) : -1 - int64_t(~bits);
    }
    double nextDouble() {
        uint64_t high = next(26);
        uint64_t low = next(27);
        return ((high << 27) + low) / double(1ULL << 53);
    }
    bool nextBoolean() {
        return next(1) != 0;
    }
    template <class Sequence> void shuffle(Sequence &a) {
        for (size_t i = 0; i < a.size(); ++i)
            std::swap(a[i], a[i + nextInt(static_cast<int>(a.size() - i))]);
    }
};
inline Random random;
inline std::string readLine(std::istream &in) {
    std::string s;
    if (!std::getline(in, s))
        throw std::runtime_error("Input ended before the exercise finished");
    if (!s.empty() && s.back() == '\r')
        s.pop_back();
    return s;
}
inline int parseInt(const std::string &s) {
    if (!std::regex_match(s, std::regex("[+-]?[0-9]+")))
        throw std::invalid_argument("Not an integer: " + s);
    return std::stoi(s);
}
inline bool isInt(const std::string &s) {
    try {
        parseInt(s);
        return true;
    } catch (const std::exception &) {
        return false;
    }
}
inline std::string lower(std::string s) {
    for (char &c : s)
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}
inline std::vector<std::string> split(const std::string &s, const std::string &separator) {
    std::regex re(separator);
    return {std::sregex_token_iterator(s.begin(), s.end(), re, -1), std::sregex_token_iterator()};
}
inline std::string readFile(const std::string &path) {
    std::ifstream in(path, std::ios::binary);
    if (!in)
        throw std::runtime_error("Cannot read " + path);
    return {std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()};
}
inline void writeFile(const std::string &path, const std::string &text) {
    std::ofstream out(path, std::ios::binary);
    if (!(out << text))
        throw std::runtime_error("Cannot write " + path);
}
inline std::string trim(std::string s) {
    auto first = s.find_first_not_of(" \t\r\n");
    return first == std::string::npos ? ""
                                      : s.substr(first, s.find_last_not_of(" \t\r\n") - first + 1);
}
inline int64_t millis() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now().time_since_epoch())
        .count();
}
} // namespace course
