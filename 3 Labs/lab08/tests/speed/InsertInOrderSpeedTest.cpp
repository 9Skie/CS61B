#include "StringUtils.hpp"
#include "Benchmark.hpp"
#include "hashmap/ULLMap.hpp"
#include "hashmap/MyHashMap.hpp"
template <class Map> void run(const std::string &name) {
    std::cout << "Number of strings for " << name << ": ";
    int n = benchmark::positiveInt();
    Map map;
    std::string s = "cat";
    benchmark::time(name, map, n, [&] {
        s = StringUtils::nextString(s);
        return s;
    });
}
int main() {
    do {
        run<ULLMap<std::string, int>>("ULLMap");
        run<MyHashMap<std::string, int>>("MyHashMap");
        run<std::unordered_map<std::string, int>>("std::unordered_map");
    } while (benchmark::again());
}
