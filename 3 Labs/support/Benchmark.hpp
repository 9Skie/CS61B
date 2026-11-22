#pragma once
#include "Support.hpp"
#include <iomanip>
#include <unordered_map>
namespace benchmark {
inline int positiveInt() {
    while (true) {
        std::string line = course::readLine(std::cin);
        if (course::isInt(line) && course::parseInt(line) > 0)
            return course::parseInt(line);
        std::cout << "Please enter a positive integer: ";
    }
}
template <class Map> void put(Map &m, const std::string &key, int i) {
    m.put(key, i);
}
template <class... Args> void put(std::map<Args...> &m, const std::string &key, int i) {
    m[key] = i;
}
template <class... Args> void put(std::unordered_map<Args...> &m, const std::string &key, int i) {
    m[key] = i;
}
template <class Map, class Generator>
void time(const std::string &name, Map &map, int n, Generator generate) {
    try {
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < n; ++i)
            put(map, generate(), i);
        double seconds =
            std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
        std::cout << name << ": " << std::fixed << std::setprecision(6) << seconds << " sec\n";
    } catch (const std::exception &e) {
        std::cout << name << ": " << e.what() << '\n';
    }
}
inline bool again() {
    std::cout << "Would you like to try more timed-tests? (y/n): ";
    auto s = course::lower(course::readLine(std::cin));
    return s != "n" && s != "no";
}
} // namespace benchmark
