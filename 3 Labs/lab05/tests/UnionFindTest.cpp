#define TEST_MAIN
#include "Test.hpp"
#include "UnionFind.hpp"

/**
 * Checks that the initial state of the disjoint sets are correct (this will pass with the skeleton
 * code, but ensure it still passes after all parts are implemented).
 */
TEST(initialStateTest) {
    UnionFind uf(4);
    CHECK(!(uf.connected(0, 1)));
    CHECK(!(uf.connected(0, 2)));
    CHECK(!(uf.connected(0, 3)));
    CHECK(!(uf.connected(1, 2)));
    CHECK(!(uf.connected(1, 3)));
    CHECK(!(uf.connected(2, 3)));
}

/**
 * Checks that invalid inputs are handled correctly.
 */
TEST(illegalFindTest) {
    UnionFind uf(4);
    CHECK_THROWS_AS(uf.find(10), std::invalid_argument);
    CHECK_THROWS_AS(uf.unite(1, 10), std::invalid_argument);
}

/**
 * Checks that union is done correctly (including the tie-breaking scheme).
 */
TEST(basicUnionTest) {
    UnionFind uf(10);
    uf.unite(0, 1);
    CHECK(uf.find(0) == 1);
    uf.unite(2, 3);
    CHECK(uf.find(2) == 3);
    uf.unite(0, 2);
    CHECK(uf.find(1) == 3);

    uf.unite(4, 5);
    uf.unite(6, 7);
    uf.unite(8, 9);
    uf.unite(4, 8);
    uf.unite(4, 6);

    CHECK(uf.find(5) == 9);
    CHECK(uf.find(7) == 9);
    CHECK(uf.find(8) == 9);

    uf.unite(9, 2);
    CHECK(uf.find(3) == 9);
}

/**
 * Unions the same item with itself. Calls on find and checks that the outputs are correct.
 */
TEST(sameUnionTest) {
    UnionFind uf(4);
    uf.unite(1, 1);
    for (int i = 0; i < 4; i += 1) {
        CHECK(uf.find(i) == i);
    }
}

/**
 * Write your own tests below here to verify for correctness. The given tests are not comprehensive.
 * Specifically, you may want to write a test for path compression and to check for the correctness
 * of all methods in your implementation.
 */
