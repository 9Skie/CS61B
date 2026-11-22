#define TEST_MAIN
#include "HashMapCases.hpp"
#include "MyHashMapFactory.hpp"
TEST(LinkedList_Generics) {
    genericsTest<std::list>();
}
TEST(LinkedList_Clear) {
    auto b = createBucketedMap<std::string, int, std::list>();
    sanityClearTest(b);
}
TEST(LinkedList_ContainsKey) {
    auto b = createBucketedMap<std::string, int, std::list>();
    containsKeyTest(b);
}
TEST(LinkedList_Get) {
    auto b = createBucketedMap<std::string, int, std::list>();
    sanityGetTest(b);
}
TEST(LinkedList_Size) {
    auto b = createBucketedMap<std::string, int, std::list>();
    sanitySizeTest(b);
}
TEST(LinkedList_Put) {
    auto b = createBucketedMap<std::string, int, std::list>();
    sanityPutTest(b);
}
TEST(LinkedList_Functionality) {
    auto a = createBucketedMap<std::string, std::string, std::list>();
    auto b = createBucketedMap<std::string, int, std::list>();
    functionalityTest(a, b);
}
TEST(LinkedList_Resize) {
    auto b = createBucketedMap<std::string, int, std::list>();
    sanityResizeTest(b, 16, 0.75);
}
TEST(LinkedList_EdgeCases) {
    auto b = createBucketedMap<Bee, int, std::list>();
    edgeCasesTest(b);
}
TEST(ArrayList_Generics) {
    genericsTest<std::vector>();
}
TEST(ArrayList_Clear) {
    auto b = createBucketedMap<std::string, int, std::vector>();
    sanityClearTest(b);
}
TEST(ArrayList_ContainsKey) {
    auto b = createBucketedMap<std::string, int, std::vector>();
    containsKeyTest(b);
}
TEST(ArrayList_Get) {
    auto b = createBucketedMap<std::string, int, std::vector>();
    sanityGetTest(b);
}
TEST(ArrayList_Size) {
    auto b = createBucketedMap<std::string, int, std::vector>();
    sanitySizeTest(b);
}
TEST(ArrayList_Put) {
    auto b = createBucketedMap<std::string, int, std::vector>();
    sanityPutTest(b);
}
TEST(ArrayList_Functionality) {
    auto a = createBucketedMap<std::string, std::string, std::vector>();
    auto b = createBucketedMap<std::string, int, std::vector>();
    functionalityTest(a, b);
}
TEST(ArrayList_Resize) {
    auto b = createBucketedMap<std::string, int, std::vector>();
    sanityResizeTest(b, 16, 0.75);
}
TEST(ArrayList_EdgeCases) {
    auto b = createBucketedMap<Bee, int, std::vector>();
    edgeCasesTest(b);
}
TEST(HashSet_Generics) {
    genericsTest<std::unordered_set>();
}
TEST(HashSet_Clear) {
    auto b = createBucketedMap<std::string, int, std::unordered_set>();
    sanityClearTest(b);
}
TEST(HashSet_ContainsKey) {
    auto b = createBucketedMap<std::string, int, std::unordered_set>();
    containsKeyTest(b);
}
TEST(HashSet_Get) {
    auto b = createBucketedMap<std::string, int, std::unordered_set>();
    sanityGetTest(b);
}
TEST(HashSet_Size) {
    auto b = createBucketedMap<std::string, int, std::unordered_set>();
    sanitySizeTest(b);
}
TEST(HashSet_Put) {
    auto b = createBucketedMap<std::string, int, std::unordered_set>();
    sanityPutTest(b);
}
TEST(HashSet_Functionality) {
    auto a = createBucketedMap<std::string, std::string, std::unordered_set>();
    auto b = createBucketedMap<std::string, int, std::unordered_set>();
    functionalityTest(a, b);
}
TEST(HashSet_Resize) {
    auto b = createBucketedMap<std::string, int, std::unordered_set>();
    sanityResizeTest(b, 16, 0.75);
}
TEST(HashSet_EdgeCases) {
    auto b = createBucketedMap<Bee, int, std::unordered_set>();
    edgeCasesTest(b);
}
TEST(Stack_Generics) {
    genericsTest<StackBucket>();
}
TEST(Stack_Clear) {
    auto b = createBucketedMap<std::string, int, StackBucket>();
    sanityClearTest(b);
}
TEST(Stack_ContainsKey) {
    auto b = createBucketedMap<std::string, int, StackBucket>();
    containsKeyTest(b);
}
TEST(Stack_Get) {
    auto b = createBucketedMap<std::string, int, StackBucket>();
    sanityGetTest(b);
}
TEST(Stack_Size) {
    auto b = createBucketedMap<std::string, int, StackBucket>();
    sanitySizeTest(b);
}
TEST(Stack_Put) {
    auto b = createBucketedMap<std::string, int, StackBucket>();
    sanityPutTest(b);
}
TEST(Stack_Functionality) {
    auto a = createBucketedMap<std::string, std::string, StackBucket>();
    auto b = createBucketedMap<std::string, int, StackBucket>();
    functionalityTest(a, b);
}
TEST(Stack_Resize) {
    auto b = createBucketedMap<std::string, int, StackBucket>();
    sanityResizeTest(b, 16, 0.75);
}
TEST(Stack_EdgeCases) {
    auto b = createBucketedMap<Bee, int, StackBucket>();
    edgeCasesTest(b);
}
TEST(ArrayDeque_Generics) {
    genericsTest<std::deque>();
}
TEST(ArrayDeque_Clear) {
    auto b = createBucketedMap<std::string, int, std::deque>();
    sanityClearTest(b);
}
TEST(ArrayDeque_ContainsKey) {
    auto b = createBucketedMap<std::string, int, std::deque>();
    containsKeyTest(b);
}
TEST(ArrayDeque_Get) {
    auto b = createBucketedMap<std::string, int, std::deque>();
    sanityGetTest(b);
}
TEST(ArrayDeque_Size) {
    auto b = createBucketedMap<std::string, int, std::deque>();
    sanitySizeTest(b);
}
TEST(ArrayDeque_Put) {
    auto b = createBucketedMap<std::string, int, std::deque>();
    sanityPutTest(b);
}
TEST(ArrayDeque_Functionality) {
    auto a = createBucketedMap<std::string, std::string, std::deque>();
    auto b = createBucketedMap<std::string, int, std::deque>();
    functionalityTest(a, b);
}
TEST(ArrayDeque_Resize) {
    auto b = createBucketedMap<std::string, int, std::deque>();
    sanityResizeTest(b, 16, 0.75);
}
TEST(ArrayDeque_EdgeCases) {
    auto b = createBucketedMap<Bee, int, std::deque>();
    edgeCasesTest(b);
}
