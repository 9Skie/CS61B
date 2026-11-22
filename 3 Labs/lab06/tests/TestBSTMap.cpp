#define TEST_MAIN
#include "Test.hpp"
#include "BSTMap.hpp"

TEST(sanityGenericsTest) {
    try {
        BSTMap<std::string, std::string> a;
        BSTMap<std::string, int> b;
        BSTMap<int, std::string> c;
        BSTMap<bool, int> e;
    } catch (const std::exception &e) {
        throw test::Failure("Unexpected exception");
    }
}

// This test assumes put/size/containsKey/get are implemented properly.
TEST(sanityClearTest) {
    BSTMap<std::string, int> b;
    for (int i = 0; i < 455; i++) {
        b.put("hi" + std::to_string(i), 1 + i);
        // make sure put is working via containsKey and get
        CHECK(b.get("hi" + std::to_string(i)) == 1 + i);
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

// Assumes `put` is implemented properly.
TEST(sanityContainsKeyTest) {
    BSTMap<std::string, int> b;
    CHECK(!(b.containsKey("waterYouDoingHere")));
    b.put("waterYouDoingHere", 0);
    CHECK(b.containsKey("waterYouDoingHere"));
}

// Assumes `put` is implemented properly.
TEST(sanityGetTest) {
    BSTMap<std::string, int> b;
    CHECK(!(b.get("starChild")));
    CHECK(b.size() == 0);
    b.put("starChild", 5);
    CHECK(b.get("starChild") == 5);
    CHECK(b.size() == 1);
    b.put("KISS", 5);
    CHECK(b.get("KISS") == 5);
    CHECK(bool(b.get("starChild")));
    CHECK(b.size() == 2);
}

// Assumes `put` is implemented properly.
TEST(sanitySizeTest) {
    BSTMap<std::string, int> b;
    CHECK(b.size() == 0);
    b.put("hi", 1);
    CHECK(b.size() == 1);
    for (int i = 0; i < 455; i++) {
        b.put("hi" + std::to_string(i), 1);
    }
    CHECK(b.size() == 456);
}

// Assumes `get` and `containsKey` are implemented properly.
TEST(sanityPutTest) {
    BSTMap<std::string, int> b;
    b.put("hi", 1);
    CHECK(b.containsKey("hi"));
    CHECK(b.get("hi") == 1);
}

// Assumes `put` is implemented properly. This test is a bit tricky - remember that
// `containsKey` should only care about the keys, not the values!
TEST(containsKeyNullTest) {
    BSTMap<std::string, int> b;
    b.put("hi", std::nullopt);
    CHECK(!(b.get("hi")));
    CHECK(b.containsKey("hi"));
}

TEST(treeTest) {
    BSTMap<std::string, std::string> b;
    b.put("d", "parmesan");
    b.put("a", "mozzarella");
    b.put("c", "swiss");
    b.put("b", "pepper jack");
    b.put("e", "gouda");

    CHECK(b.size() == 5);
    CHECK(b.get("d") == "parmesan");
    CHECK(b.get("a") == "mozzarella");
    CHECK(b.get("c") == "swiss");
    CHECK(b.get("b") == "pepper jack");
    CHECK(b.get("e") == "gouda");

    b.put("b", "provolone");
    CHECK(b.size() == 5);
    CHECK(b.get("b") == "provolone");
}
