#include "StringUtils.hpp"
#include "Benchmark.hpp"
#include "../hashmap/MyHashMapFactory.hpp"
template <template <class...> class Bucket> void run(const std::string &name, int n, int length) {
    auto map = createBucketedMap<std::string, int, Bucket>();
    benchmark::time(name, map, n, [&] { return StringUtils::randomString(length); });
}
int main() {
    std::cout << "String length: ";
    int length = benchmark::positiveInt();
    do {
        std::cout << "Number of strings: ";
        int n = benchmark::positiveInt();
        run<std::vector>("vector", n, length);
        run<std::list>("list", n, length);
        run<std::unordered_set>("unordered_set", n, length);
        run<StackBucket>("stack", n, length);
        run<std::deque>("deque", n, length);
    } while (benchmark::again());
}
