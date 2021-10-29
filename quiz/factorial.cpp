#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

int factorial(int n)
{
    return n > 1 ? factorial(n - 1) * n : 1;
}

TEST_CASE("Test factorial()")
{
    CHECK(factorial(0) == 1);
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(4) == 24);
    CHECK(factorial(5) == 120);
    CHECK(factorial(6) == 720);
    CHECK(factorial(7) == 5040);
    CHECK(factorial(8) == 40320);
    CHECK(factorial(9) == 362880);
    CHECK(factorial(10) == 3628800);
}
