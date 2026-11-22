#pragma once
#include "Support.hpp"
namespace StringUtils {
inline course::Random r;
inline void setSeed(int64_t seed) {
    r.setSeed(seed);
}
inline std::string randomString(int length) {
    std::string result(length, 'a');
    for (char &c : result)
        c += r.nextInt(26);
    return result;
}
inline bool isLowerCase(const std::string &s) {
    return std::regex_match(s, std::regex("[a-z]*"));
}
inline bool isAllzs(const std::string &s) {
    return std::regex_match(s, std::regex("[z]+"));
}
inline std::string nextString(std::string s) {
    if (isAllzs(s))
        return std::string(s.size() + 1, 'a');
    int i = static_cast<int>(s.size()) - 1;
    while (s.at(i) == 'z') {
        s.at(i) = 'a';
        --i;
    }
    ++s.at(i);
    return s;
}
} // namespace StringUtils
