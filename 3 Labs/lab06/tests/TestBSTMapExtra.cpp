#define TEST_MAIN
#include "Test.hpp"
#include "BSTMap.hpp"

/*
 * Sanity test for keySet, only here because it's optional
 */
TEST(sanityKeySetTest) {
    BSTMap<std::string, int> b;
    std::set<std::string> values;
    for (int i = 0; i < 455; i++) {
        b.put("hi" + std::to_string(i), 1);
        values.insert("hi" + std::to_string(i));
    }
    CHECK(b.size() == 455); // keys are there
    std::set<std::string> keySet = b.keySet();
    CHECK(values == keySet);
    CHECK(keySet == values);
}

/* Remove Test
 *
 * Note for testRemoveRoot:
 *
 * Just checking that c is gone (perhaps incorrectly)
 * assumes that remove is BST-structure preserving.
 *
 * More exhaustive tests could be done to verify
 * implementation of remove, but that would require doing
 * things like checking for inorder vs. preorder swaps,
 * and is unnecessary in this simple BST implementation.
 */
TEST(testRemoveRoot) {
    BSTMap<std::string, std::string> q;
    q.put("c", "a");
    q.put("b", "a");
    q.put("a", "a");
    q.put("d", "a");
    q.put("e", "a"); // a b c d e
    CHECK(q.remove("c") == "a");
    CHECK(!(q.containsKey("c")));
    CHECK(!(q.remove("c")));
    CHECK(q.containsKey("a"));
    CHECK(q.containsKey("b"));
    CHECK(q.containsKey("d"));
    CHECK(q.containsKey("e"));
}

/* Remove Test 2
 * test the 3 different cases of remove
 */
TEST(testRemoveThreeCases) {
    BSTMap<std::string, std::string> q;
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

/* Remove Test 3
 *  Checks that remove works correctly on root nodes
 *  when the node has only 1 or 0 children on either side. */
TEST(testRemoveRootEdge) {
    BSTMap<char, int> rightChild;
    rightChild.put('A', 1);
    rightChild.put('B', 2);
    CHECK(rightChild.remove('A') == 1);
    for (int i = 0; i < 10; i++) {
        rightChild.put((char)('C' + i), 3 + i);
    }
    rightChild.put('A', 100);
    CHECK(rightChild.remove('D') == 4);
    CHECK(rightChild.remove('G') == 7);
    CHECK(rightChild.remove('A') == 100);
    CHECK(rightChild.size() == 9);

    BSTMap<char, int> leftChild;
    leftChild.put('B', 1);
    leftChild.put('A', 2);
    CHECK(leftChild.remove('B') == 1);
    CHECK(leftChild.size() == 1);
    CHECK(!(leftChild.get('B')));

    BSTMap<char, int> noChild;
    noChild.put('Z', 15);
    CHECK(noChild.remove('Z') == 15);
    CHECK(noChild.size() == 0);
    CHECK(!(noChild.get('Z')));
}
