#define TEST_MAIN
#include "HashMapCases.hpp"
TEST(testGenerics) {
    genericsTest<std::list>();
}
TEST(testClear) {
    MyHashMap<std::string, int> b;
    sanityClearTest(b);
}
TEST(testContainsKey) {
    MyHashMap<std::string, int> b;
    containsKeyTest(b);
}
TEST(testGet) {
    MyHashMap<std::string, int> b;
    sanityGetTest(b);
}
TEST(testSize) {
    MyHashMap<std::string, int> b;
    sanitySizeTest(b);
}
TEST(testPut) {
    MyHashMap<std::string, int> b;
    sanityPutTest(b);
}
TEST(testFunctionality) {
    MyHashMap<std::string, std::string> a;
    MyHashMap<std::string, int> b;
    functionalityTest(a, b);
}
TEST(testResize) {
    MyHashMap<std::string, int> a, b(32), c(64, 0.5);
    sanityResizeTest(a, 16, 0.75);
    sanityResizeTest(b, 32, 0.75);
    sanityResizeTest(c, 64, 0.5);
}
TEST(testEdgeCases) {
    MyHashMap<Bee, int> b;
    edgeCasesTest(b);
}
