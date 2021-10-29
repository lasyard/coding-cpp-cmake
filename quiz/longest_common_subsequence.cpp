#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <cstring>

int longestCommonSubsequence(const char *a, const char *b)
{
    if (a == nullptr || b == nullptr) {
        return 0;
    }
    int la = strlen(a);
    int lb = strlen(b);
    int **l = new int *[la + 1];
    for (int i = 0; i < la + 1; i++) {
        l[i] = new int[lb + 1];
        l[i][0] = 0;
    }
    for (int j = 1; j < lb + 1; j++) {
        l[0][j] = 0;
    }
    for (int i = 0; i < la; i++) {
        for (int j = 0; j < lb; j++) {
            if (a[i] == b[j]) {
                l[i + 1][j + 1] = l[i][j] + 1;
            } else if (l[i][j + 1] > l[i + 1][j]) {
                l[i + 1][j + 1] = l[i][j + 1];
            } else {
                l[i + 1][j + 1] = l[i + 1][j];
            }
        }
    }
    int r = l[la][lb];
    for (int i = 0; i < la + 1; i++) {
        delete[] l[i];
    }
    delete[] l;
    return r;
}

TEST_CASE("Test longestCommonSubsequence()")
{
    SUBCASE("null abc => 0")
    {
        CHECK(longestCommonSubsequence(nullptr, "abc") == 0);
    }
    SUBCASE("empty abc => 0")
    {
        CHECK(longestCommonSubsequence("", "abc") == 0);
    }
    SUBCASE("abc defghi => 0")
    {
        CHECK(longestCommonSubsequence("abc", "defghi") == 0);
    }
    SUBCASE("adbec deafgbhci => 3")
    {
        CHECK(longestCommonSubsequence("adbec", "deafgbhci") == 3);
    }
    SUBCASE("abcd aabdcfgahcid => 4")
    {
        CHECK(longestCommonSubsequence("abcd", "aabdcfgahcid") == 4);
    }
}
