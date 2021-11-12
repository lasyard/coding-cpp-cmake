#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "fraction.h"
#include "gcd_lcm.h"

TEST_CASE("Test gcd()")
{
    SUBCASE("gcd(5, 3) == 1")
    {
        CHECK(gcd(5, 3) == 1);
    }
    SUBCASE("gcd(8, 6) == 2")
    {
        CHECK(gcd(8, 6) == 2);
    }
    SUBCASE("gcd(15, 5) == 5")
    {
        CHECK(gcd(15, 5) == 5);
    }
    SUBCASE("gcd(19, 5) == 1")
    {
        CHECK(gcd(19, 5) == 1);
    }
}

TEST_CASE("Test lcm()")
{
    SUBCASE("lcm(5, 3) == 15")
    {
        CHECK(lcm(5, 3) == 15);
    }
    SUBCASE("lcm(8, 6) == 2")
    {
        CHECK(lcm(8, 6) == 24);
    }
    SUBCASE("lcm(15, 5) == 5")
    {
        CHECK(lcm(15, 5) == 15);
    }
    SUBCASE("lcm(19, 5) == 95")
    {
        CHECK(lcm(19, 5) == 95);
    }
}

TEST_CASE("Test int fraction conversion")
{
    struct fraction f = int_to_fraction(3);
    CHECK(f.nume == 3);
    CHECK(f.deno == 1);
    CHECK(fraction_to_int(f) == 3);
}

TEST_CASE("Test fraction comparision")
{
    struct fraction a = fraction_make(7, 3);
    struct fraction b = fraction_make(8, 4);
    CHECK(fraction_compare(a, b) == 1);
    CHECK(fraction_compare_int(a, 2) == 1);
    CHECK(fraction_compare_int(b, 2) == 0);
}

TEST_CASE("Test fraction_recude()")
{
    struct fraction f = fraction_make(8, 6);
    f = fraction_reduce(f);
    CHECK(f.nume == 4);
    CHECK(f.deno == 3);
}

TEST_CASE("Test fraction arithmetic")
{
    struct fraction a = fraction_make(7, 3);
    struct fraction b = fraction_make(6, 5);
    SUBCASE("Test add")
    {
        struct fraction f = fraction_add(a, b);
        CHECK(f.nume == 53);
        CHECK(f.deno == 15);
    }
    SUBCASE("Test sub")
    {
        struct fraction f = fraction_sub(a, b);
        CHECK(f.nume == 17);
        CHECK(f.deno == 15);
    }
    SUBCASE("Test mul")
    {
        struct fraction f = fraction_mul(a, b);
        CHECK(f.nume == 14);
        CHECK(f.deno == 5);
    }
    SUBCASE("Test div")
    {
        struct fraction f = fraction_div(a, b);
        CHECK(f.nume == 35);
        CHECK(f.deno == 18);
    }
    SUBCASE("Test neg")
    {
        struct fraction f = fraction_neg(a);
        CHECK(f.nume == -7);
        CHECK(f.deno == 3);
    }
    SUBCASE("Text recip")
    {
        struct fraction f = fraction_recip(a);
        CHECK(f.nume == 3);
        CHECK(f.deno == 7);
    }
}
