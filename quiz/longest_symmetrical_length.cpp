#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

static int searchSymmetricalLength(const char *str, const char *left, const char *right)
{
    while (left >= str && *right != '\0' && *left == *right) {
        left--;
        right++;
    }
    return right - left - 1;
}

int longestSymmetricalLength(const char *str)
{
    if (str == nullptr || *str == '\0') {
        return 0;
    }
    int max_len = 1;
    int len;
    const char *p = str;
    while (*p != '\0') {
        len = searchSymmetricalLength(str, p, p);
        if (len > max_len) {
            max_len = len;
        }
        len = searchSymmetricalLength(str, p, p + 1);
        if (len > max_len) {
            max_len = len;
        }
        p++;
    }
    return max_len;
}

TEST_CASE("Test longestSymmetricalLength()")
{
    SUBCASE("null => 0")
    {
        CHECK(longestSymmetricalLength(nullptr) == 0);
    }
    SUBCASE("empty => 0")
    {
        CHECK(longestSymmetricalLength("") == 0);
    }
    SUBCASE("a => 1")
    {
        CHECK(longestSymmetricalLength("a") == 1);
    }
    SUBCASE("abbacdc => 4")
    {
        CHECK(longestSymmetricalLength("abbacdc") == 4);
    }
    SUBCASE("abacddcabadc => 10")
    {
        CHECK(longestSymmetricalLength("abacddcabadc") == 10);
    }
}
