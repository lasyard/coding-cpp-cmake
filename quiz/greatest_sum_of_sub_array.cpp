#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <cassert>

int greatestSumOfSubArray(int a[], int size)
{
    assert(a != nullptr);
    assert(size >= 0);
    int *p;
    int current = 0;
    int greatest = current;
    for (p = a; p < a + size; p++) {
        current += *p;
        if (current < 0) {
            current = 0;
        }
        if (greatest < current) {
            greatest = current;
        }
    }
    if (greatest == 0) {
        greatest = a[0];
        for (p = a + 1; p < a + size; p++) {
            if (greatest < *p) {
                greatest = *p;
            }
        }
    }
    return greatest;
}

TEST_CASE("Test greatestSumOfSubArray()")
{
    SUBCASE("all negative")
    {
        int a[] = {-3, -2, -1, -2};
        CHECK(greatestSumOfSubArray(a, sizeof(a) / sizeof(int)) == -1);
    }
    SUBCASE("negative in the middle")
    {
        int a[] = {1, 0, 2, -1, 3, -2, -3, 1};
        CHECK(greatestSumOfSubArray(a, sizeof(a) / sizeof(int)) == 5);
    }
    SUBCASE("negative int the middle and discarded")
    {
        int a[] = {1, 0, 2, -1, 3, -2, -3, 1, 6};
        CHECK(greatestSumOfSubArray(a, sizeof(a) / sizeof(int)) == 7);
    }
}
