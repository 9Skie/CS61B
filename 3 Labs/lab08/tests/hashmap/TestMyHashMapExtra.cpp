#define TEST_MAIN
#include "Test.hpp"
#include "hashmap/MyHashMap.hpp"

TEST(testRemove) {
    MyHashMap<std::string, std::string> q;
    q.put("c", "a");
    q.put("b", "a");
    q.put("a", "a");
    q.put("d", "a");
    q.put("e", "a"); // a b c d e
    CHECK(bool(q.remove("c")));
    CHECK(!(q.remove("f")));
    CHECK(!(q.containsKey("c")));
    CHECK(q.containsKey("a"));
    CHECK(q.containsKey("b"));
    CHECK(q.containsKey("d"));
    CHECK(q.containsKey("e"));
}

/**
 * Remove Test 2
 * Test the 3 different cases of remove
 */
TEST(testRemoveThreeCases) {
    MyHashMap<std::string, std::string> q;
    q.put("c", "a");
    q.put("b", "a");
    q.put("a", "a");
    q.put("d", "a");
    q.put("e", "a");            // a b c d e
    CHECK(bool(q.remove("e"))); // a b c d
    CHECK(q.containsKey("a"));
    CHECK(q.containsKey("b"));
    CHECK(q.containsKey("c"));
    CHECK(q.containsKey("d"));
    CHECK(bool(q.remove("c"))); // a b d
    CHECK(q.containsKey("a"));
    CHECK(q.containsKey("b"));
    CHECK(q.containsKey("d"));
    q.put("f", "a");            // a b d f
    CHECK(bool(q.remove("d"))); // a b f
    CHECK(q.containsKey("a"));
    CHECK(q.containsKey("b"));
    CHECK(q.containsKey("f"));
}

TEST(sanityKeySetTest) {
    MyHashMap<std::string, int> b;
    std::set<std::string> values;
    for (int i = 0; i < 455; i++) {
        b.put("hi" + std::to_string(i), 1);
        values.insert("hi" + std::to_string(i));
    }
    CHECK(455 == b.size()); // keys are there
    std::set<std::string> keySet = b.keySet();
    CHECK(values == keySet);
    CHECK(keySet == values);
}
