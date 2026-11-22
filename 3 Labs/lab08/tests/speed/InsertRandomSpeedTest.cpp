#include "StringUtils.hpp"
#include "Benchmark.hpp"
#include "hashmap/ULLMap.hpp"
#include "hashmap/MyHashMap.hpp"
int main() {
    std::cout
        << "This program inserts random strings as <string, int> pairs.\nLength of each string: ";
    int length = benchmark::positiveInt();
    do {
        std::cout << "Number of strings: ";
        int n = benchmark::positiveInt();
        ULLMap<std::string, int> list;
        MyHashMap<std::string, int> student;
        std::map<std::string, int> tree;
        std::unordered_map<std::string, int> hash;
        auto generate = [&] { return StringUtils::randomString(length); };
        benchmark::time("ULLMap", list, n, generate);
        benchmark::time("MyHashMap", student, n, generate);
        benchmark::time("std::map", tree, n, generate);
        benchmark::time("std::unordered_map", hash, n, generate);
    } while (benchmark::again());
}
