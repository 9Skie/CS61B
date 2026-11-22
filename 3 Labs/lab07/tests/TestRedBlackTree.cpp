#define TEST_MAIN
#include "Test.hpp"
#include "RedBlackTree.hpp"
struct TestableRedBlackTree : RedBlackTree<int> {
    int callsToFlipColors = 0, callsToRotateRight = 0, callsToRotateLeft = 0;
    void flipColors(Node node) override {
        ++callsToFlipColors;
        RedBlackTree::flipColors(node);
    }
    Node rotateRight(Node node) override {
        ++callsToRotateRight;
        return RedBlackTree::rotateRight(node);
    }
    Node rotateLeft(Node node) override {
        ++callsToRotateLeft;
        return RedBlackTree::rotateLeft(node);
    }
};

/*
 * Test class for RedBlackTree.hpp
 *
 * We've provided LLRB Tree representations after every operations in this file as comments to help
 * you debug.
 *
 *
 * Black Nodes are represented with () and red nodes are represented with ()*
 * Left children are listed before right children.
 */

/*
Tests for a very basic case of rotating right. This does not check for color flips, but only if the
nodes are in the proper place after rotating right. Note that we have not provided any basic tests
for rotate left, but implementation details for rotate right and rotate left should be symmetrical.
 */
TEST(testBasicRotateRight) {
    // Insert 10, 9, 8
    TestableRedBlackTree rbtree;
    CHECK(!(rbtree.root));

    RedBlackTree<int>::Node node1 =
        std::make_shared<RedBlackTree<int>::RBTreeNode>(true, 10, nullptr, nullptr);
    RedBlackTree<int>::Node node2 =
        std::make_shared<RedBlackTree<int>::RBTreeNode>(false, 9, nullptr, nullptr);
    RedBlackTree<int>::Node node3 =
        std::make_shared<RedBlackTree<int>::RBTreeNode>(false, 8, nullptr, nullptr);
    node1->left = node2;
    node2->left = node3;

    RedBlackTree<int>::Node newRoot = rbtree.rotateRight(node1);
    CHECK(newRoot);
    CHECK(newRoot->item == 9);
    CHECK(newRoot->right->item == 10);
    CHECK(newRoot->left->item == 8);
}

TEST(testInsertSimple) {
    TestableRedBlackTree rbtree;

    /*
    LLRB Tree representation:

     */
    CHECK(!(rbtree.root));

    rbtree.insert(10);

    /*
    LLRB Tree representation:
       (10)

     */

    // root
    CHECK(bool(rbtree.root));
    CHECK(rbtree.root->isBlack);
    CHECK(rbtree.root->item == 10);

    // left
    CHECK(!(rbtree.root->left));

    // right
    CHECK(!(rbtree.root->right));

    rbtree.insert(5);

    /*
    LLRB Tree representation:
        (10)
        └── (5)*

     */

    // root
    CHECK(bool(rbtree.root));
    CHECK(rbtree.root->isBlack);
    CHECK(rbtree.root->item == 10);

    // left
    CHECK(bool(rbtree.root->left));
    CHECK(!(rbtree.root->left->isBlack));
    CHECK(rbtree.root->left->item == 5);

    // left->left
    CHECK(!(rbtree.root->left->left));

    // left->right
    CHECK(!(rbtree.root->left->right));

    // right
    CHECK(!(rbtree.root->right));

    CHECK(rbtree.callsToFlipColors == 0);
    CHECK(rbtree.callsToRotateLeft == 0);
    CHECK(rbtree.callsToRotateRight == 0);
}

TEST(testInsertFlipColor) {
    TestableRedBlackTree rbtree;
    rbtree.insert(10);
    rbtree.insert(5);
    rbtree.insert(15);

    /*
    LLRB Tree Representation:
        (10)
        ├── (5)
        └── (15)

     */

    // root
    CHECK(bool(rbtree.root));
    CHECK(rbtree.root->isBlack);
    CHECK(rbtree.root->item == 10);

    // left
    CHECK(bool(rbtree.root->left));
    CHECK(rbtree.root->left->isBlack);
    CHECK(rbtree.root->left->item == 5);

    // left->left
    CHECK(!(rbtree.root->left->left));

    // left->right
    CHECK(!(rbtree.root->left->right));

    // right
    CHECK(bool(rbtree.root->right));
    CHECK(rbtree.root->right->isBlack);
    CHECK(rbtree.root->right->item == 15);

    // right->left
    CHECK(!(rbtree.root->right->left));

    // right->right
    CHECK(!(rbtree.root->right->right));

    CHECK(rbtree.callsToFlipColors == 1);
    CHECK(rbtree.callsToRotateLeft == 0);
    CHECK(rbtree.callsToRotateRight == 0);
}

TEST(testInsertRotateLeft) {
    TestableRedBlackTree rbtree;
    rbtree.insert(10);
    rbtree.insert(15);

    /*
    LLRB Tree Representation:
        (15)
        └── (10)*

     */

    // root
    CHECK(bool(rbtree.root));
    CHECK(rbtree.root->isBlack);
    CHECK(rbtree.root->item == 15);

    // left
    CHECK(bool(rbtree.root->left));
    CHECK(!(rbtree.root->left->isBlack));
    CHECK(rbtree.root->left->item == 10);

    // left->left
    CHECK(!(rbtree.root->left->left));

    // left->right
    CHECK(!(rbtree.root->left->right));

    // right
    CHECK(!(rbtree.root->right));

    CHECK(rbtree.callsToFlipColors == 0);
    CHECK(rbtree.callsToRotateLeft == 1);
    CHECK(rbtree.callsToRotateRight == 0);
}

TEST(testInsertRotateRight) {

    TestableRedBlackTree rbtree;
    rbtree.insert(10);
    rbtree.insert(5);
    rbtree.insert(3);

    /*
    LLRB Tree Representation:
        (5)
        └── (3)
        └── (10)

     */

    // root
    CHECK(bool(rbtree.root));
    CHECK(rbtree.root->isBlack);
    CHECK(rbtree.root->item == 5);

    // left
    CHECK(bool(rbtree.root->left));
    CHECK(rbtree.root->left->isBlack);
    CHECK(rbtree.root->left->item == 3);

    // left->left
    CHECK(!(rbtree.root->left->left));

    // left->right
    CHECK(!(rbtree.root->left->right));

    // right
    CHECK(bool(rbtree.root->right));
    CHECK(rbtree.root->right->isBlack);
    CHECK(rbtree.root->right->item == 10);

    // right->left
    CHECK(!(rbtree.root->right->left));

    // right->right
    CHECK(!(rbtree.root->right->right));

    // Not possible to test rotate right without calling color flip in the same insert, if
    // implemented correctly
    CHECK(rbtree.callsToFlipColors == 1);
    CHECK(rbtree.callsToRotateLeft == 0);
    CHECK(rbtree.callsToRotateRight == 1);
}

TEST(testInsertAllFixes) {
    TestableRedBlackTree rbtree;

    rbtree.insert(10);
    rbtree.insert(5);
    rbtree.insert(7);

    /*
    LLRB Tree Representation:
        (7)
        ├── (5)
        └── (10)

     */

    // root
    CHECK(bool(rbtree.root));
    CHECK(rbtree.root->isBlack);
    CHECK(rbtree.root->item == 7);

    // left
    CHECK(bool(rbtree.root->left));
    CHECK(rbtree.root->left->isBlack);
    CHECK(rbtree.root->left->item == 5);

    // left->left
    CHECK(!(rbtree.root->left->left));

    // left->right
    CHECK(!(rbtree.root->left->right));

    // right
    CHECK(bool(rbtree.root->right));
    CHECK(rbtree.root->right->isBlack);
    CHECK(rbtree.root->right->item == 10);

    // right->left
    CHECK(!(rbtree.root->right->left));

    // right->right
    CHECK(!(rbtree.root->right->right));

    CHECK(rbtree.callsToFlipColors == 1);
    CHECK(rbtree.callsToRotateLeft == 1);
    CHECK(rbtree.callsToRotateRight == 1);
}

TEST(testInsertUpwardPropagation) {
    TestableRedBlackTree rbtree;

    rbtree.insert(5);
    rbtree.insert(11);
    rbtree.insert(3);
    rbtree.insert(9);
    rbtree.insert(7);
    rbtree.insert(1);
    rbtree.insert(2);

    /*
    LLRB Tree Representation:
        (5)
        ├── (2)
        │   ├── (1)
        │   └── (3)
        └── (9)
            ├── (7)
            └── (11)

     */

    // root
    CHECK(bool(rbtree.root));
    CHECK(rbtree.root->isBlack);
    CHECK(rbtree.root->item == 5);

    // left
    CHECK(bool(rbtree.root->left));
    CHECK(rbtree.root->left->isBlack);
    CHECK(rbtree.root->left->item == 2);

    // left->left
    CHECK(bool(rbtree.root->left->left));
    CHECK(rbtree.root->left->left->isBlack);
    CHECK(rbtree.root->left->left->item == 1);

    // left->right
    CHECK(bool(rbtree.root->left->right));
    CHECK(rbtree.root->left->right->isBlack);
    CHECK(rbtree.root->left->right->item == 3);

    // right
    CHECK(bool(rbtree.root->right));
    CHECK(rbtree.root->right->isBlack);
    CHECK(rbtree.root->right->item == 9);

    // right->left
    CHECK(bool(rbtree.root->right->left));
    CHECK(rbtree.root->right->left->isBlack);
    CHECK(rbtree.root->right->left->item == 7);

    // right->right
    CHECK(bool(rbtree.root->right->right));
    CHECK(rbtree.root->right->right->isBlack);
    CHECK(rbtree.root->right->right->item == 11);

    CHECK(rbtree.callsToFlipColors == 4);
    CHECK(rbtree.callsToRotateLeft == 3);
    CHECK(rbtree.callsToRotateRight == 4);
}
