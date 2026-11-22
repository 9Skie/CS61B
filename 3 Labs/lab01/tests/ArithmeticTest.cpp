#define TEST_MAIN
#include "Test.hpp"
#include "Arithmetic.hpp"
TEST(testProduct) {
    CHECK(Arithmetic::product(5, 6) == 30);
    CHECK(Arithmetic::product(5, -6) == -30);
    CHECK(Arithmetic::product(0, -6) == 0);
    CHECK(Arithmetic::product(-5, -6) == 30);
}
TEST(testSum) {
    CHECK(Arithmetic::sum(5, 6) == 11);
    CHECK(Arithmetic::sum(5, -6) == -1);
    CHECK(Arithmetic::sum(0, -6) == -6);
    CHECK(Arithmetic::sum(6, -6) == 0);
    CHECK(Arithmetic::sum(-5, -5) == -10);
}
