#pragma once
#include "Test.hpp"
#include "hashmap/MyHashMap.hpp"
// The original collision fixture uses a deliberately non-transitive equality.
// A small explicit reference list avoids passing that invalid equivalence to
// std::unordered_map (which requires an equivalence relation).
struct Bee {
    int b;
    explicit Bee(int value) : b(value) {}
    bool operator==(const Bee &other) const {
        return std::abs(b - other.b) < 61;
    }
    bool operator<(const Bee &other) const {
        return b < other.b;
    }
};
namespace std {
template <> struct hash<Bee> {
    size_t operator()(const Bee &) const {
        return static_cast<size_t>(-61);
    }
};
} // namespace std
struct BeeReference {
    std::vector<std::pair<Bee, int>> entries;
    void put(Bee key, int value) {
        for (auto &e : entries)
            if (e.first == key) {
                e.second = value;
                return;
            }
        entries.emplace_back(key, value);
    }
    std::optional<int> get(Bee key) const {
        for (auto &e : entries)
            if (e.first == key)
                return e.second;
        return std::nullopt;
    }
    bool containsKey(Bee key) const {
        return get(key).has_value();
    }
    int size() const {
        return static_cast<int>(entries.size());
    }
};
template <template <class...> class Bucket>
void sanityClearTest(MyHashMap<std::string, int, Bucket> &b) {
    for (int i = 0; i < 455; i++) {
        b.put("hi" + std::to_string(i), i);
        // make sure put is working via containsKey and get
        CHECK(b.get("hi" + std::to_string(i)) == i);
        CHECK(b.containsKey("hi" + std::to_string(i)));
    }
    CHECK(b.size() == 455);
    b.clear();
    CHECK(b.size() == 0);
    for (int i = 0; i < 455; i++) {
        CHECK(!(b.get("hi" + std::to_string(i))));
        CHECK(!(b.containsKey("hi" + std::to_string(i))));
    }
}
template <template <class...> class Bucket>
void containsKeyTest(MyHashMap<std::string, int, Bucket> &b) {
    CHECK(!(b.containsKey("waterYouDoingHere")));
    b.put("waterYouDoingHere", 0);
    CHECK(b.containsKey("waterYouDoingHere"));

    // Recall that even with a std::nullopt value, containsKey should return true
    b.put("hashBrowns", std::nullopt);
    CHECK(b.containsKey("hashBrowns"));
}
template <template <class...> class Bucket>
void sanityGetTest(MyHashMap<std::string, int, Bucket> &b) {
    CHECK(!(b.get("starChild")));
    b.put("starChild", 5);
    CHECK(b.get("starChild") == 5);
    b.put("KISS", 5);
    CHECK(b.get("KISS") == 5);
    CHECK(b.get("starChild") == 5);
}
template <template <class...> class Bucket>
void sanitySizeTest(MyHashMap<std::string, int, Bucket> &b) {
    CHECK(b.size() == 0);
    b.put("hi", 1);
    CHECK(b.size() == 1);
    for (int i = 0; i < 455; i++) {
        b.put("hi" + std::to_string(i), 1);
    }
    CHECK(b.size() == 456);
}
template <template <class...> class Bucket>
void sanityPutTest(MyHashMap<std::string, int, Bucket> &b) {
    b.put("hi", 1);
    CHECK(b.containsKey("hi"));
    CHECK(b.get("hi") == 1);
}
template <template <class...> class Bucket>
void functionalityTest(MyHashMap<std::string, std::string, Bucket> &dictionary,
                       MyHashMap<std::string, int, Bucket> &studentIDs) {
    CHECK(dictionary.size() == 0);

    // can put objects in dictionary and get them
    dictionary.put("hello", "world");
    CHECK(dictionary.containsKey("hello"));
    CHECK(dictionary.get("hello") == "world");
    CHECK(dictionary.size() == 1);

    // putting with existing key updates the value
    dictionary.put("hello", "kevin");
    CHECK(dictionary.size() == 1);
    CHECK(dictionary.get("hello") == "kevin");

    // putting key in multiple times does not affect behavior
    studentIDs.put("sarah", 12345);
    CHECK(studentIDs.size() == 1);
    CHECK(studentIDs.get("sarah") == 12345);
    studentIDs.put("alan", 345);
    CHECK(studentIDs.size() == 2);
    CHECK(studentIDs.get("sarah") == 12345);
    CHECK(studentIDs.get("alan") == 345);
    studentIDs.put("alan", 345);
    CHECK(studentIDs.size() == 2);
    CHECK(studentIDs.get("sarah") == 12345);
    CHECK(studentIDs.get("alan") == 345);
    studentIDs.put("alan", 345);
    CHECK(studentIDs.size() == 2);
    CHECK(studentIDs.get("sarah") == 12345);
    CHECK(studentIDs.get("alan") == 345);
    CHECK(studentIDs.containsKey("sarah"));
    CHECK(studentIDs.containsKey("alan"));

    // handle values being the same
    CHECK(studentIDs.get("alan") == 345);
    studentIDs.put("evil alan", 345);
    CHECK(studentIDs.get("evil alan") == 345);
    CHECK(studentIDs.get("alan") == studentIDs.get("evil alan"));
}
template <template <class...> class Bucket> void edgeCasesTest(MyHashMap<Bee, int, Bucket> &map) {

    BeeReference ref;

    Bee b1(1);
    map.put(b1, 1);
    ref.put(b1, 1);
    CHECK(map.containsKey(b1) == ref.containsKey(b1));

    Bee b2(2);
    CHECK(map.containsKey(b2) == ref.containsKey(b2));

    map.put(b2, 2);
    ref.put(b2, 2);
    CHECK(map.get(b1) == ref.get(b1));
    CHECK(map.get(b2) == ref.get(b2));
    CHECK(map.containsKey(b1) == ref.containsKey(b1));
    CHECK(map.containsKey(b2) == ref.containsKey(b2));

    Bee b61(-61);
    CHECK(map.get(b61) == ref.get(b61));
    CHECK(map.containsKey(b61) == ref.containsKey(b61));
    CHECK(map.size() == ref.size());

    map.put(b61, -61);
    ref.put(b61, -61);
    CHECK(map.get(b1) == ref.get(b1));
    CHECK(map.get(b2) == ref.get(b2));
    CHECK(map.get(b61) == ref.get(b61));
    CHECK(map.size() == ref.size());

    // trigger a resize
    for (int m = 3; m <= 61; m++) {
        Bee bm(m * 61);
        CHECK(map.containsKey(bm) == ref.containsKey(bm));
        CHECK(map.get(bm) == ref.get(bm));
        map.put(bm, m * 61);
        ref.put(bm, m * 61);
        CHECK(map.containsKey(bm) == ref.containsKey(bm));
        CHECK(map.get(bm) == ref.get(bm));
        CHECK(map.get(b61) == ref.get(b61));
        CHECK(map.size() == ref.size());
    }

    for (int n = 0; n < 61; n++) {
        Bee bn(n);
        map.put(bn, n);
        ref.put(bn, n);
        CHECK(map.containsKey(b1) == ref.containsKey(b1));
        CHECK(map.containsKey(bn) == ref.containsKey(bn));
        CHECK(map.get(b1) == ref.get(b1));
        CHECK(map.get(bn) == ref.get(bn));
        CHECK(map.size() == ref.size());
    }
}

template <template <class...> class Bucket>
void sanityResizeTest(MyHashMap<std::string, int, Bucket> &m, int initialCapacity,
                      double loadFactor) {
    auto start = std::chrono::steady_clock::now();
    int capacity = m.bucketCount();
    CHECK(capacity == initialCapacity);
    for (int i = 0; i < 100000; ++i) {
        m.put("hi" + std::to_string(i), i);
        if (1.0 * i / capacity > loadFactor) {
            CHECK(m.bucketCount() > capacity);
            capacity = m.bucketCount();
        }
        CHECK(std::chrono::steady_clock::now() - start < std::chrono::seconds(10));
    }
}
template <template <class...> class Bucket> void genericsTest() {
    MyHashMap<std::string, std::string, Bucket> a;
    MyHashMap<std::string, int, Bucket> b;
    MyHashMap<int, std::string, Bucket> c;
    MyHashMap<bool, int, Bucket> d;
}
