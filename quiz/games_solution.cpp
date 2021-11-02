/**
 * See https://lasy.readthedocs.io/quiz/math/games_solution.html
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <cstdio>

#define MAX_NUMBER  100
#define MAX_MAPPING 256

static bool *buildFlags()
{
    bool *f = new bool[MAX_MAPPING];
    for (int i = 0; i < MAX_MAPPING; i++) {
        f[i] = false;
    }
    return f;
}

/* For Game 2 */
static bool *game2SieveFor(int e[], int n)
{
    bool *f = buildFlags();
    if (n >= 2) {
        for (int i = 0; i <= (n - 2) / 2; i++) {
            f[e[i] ^ e[n - 2 - i]] = true;
        }
    }
    if (n >= 1) {
        for (int i = 0; i <= (n - 1) / 2; i++) {
            f[e[i] ^ e[n - 1 - i]] = true;
        }
    }
    return f;
}

/* For Game 3 */
static bool *game3SieveFor(int e[], int n)
{
    bool *f = buildFlags();
    for (int i = 1; i < (n + 1) / 2; i++) {
        f[e[i] ^ e[n - i]] = true;
    }
    return f;
}

int *doSieve(bool *(*sieve)(int e[], int n))
{
    int *e = new int[MAX_NUMBER];
    e[0] = 0;
    for (int i = 1; i < MAX_NUMBER; i++) {
        bool *f = sieve(e, i);
        int j;
        for (j = 0; j < MAX_MAPPING && f[j]; j++)
            ;
        e[i] = j;
        delete[] f;
    }
    return e;
}

void print(int e[])
{
    int max = 0;
    for (int j = 1; j < MAX_NUMBER; ++j) {
        if (e[j] > max) {
            max = e[j];
        }
    }
    for (int i = 0; i <= max; i++) {
        printf("%2d: ", i);
        for (int j = 1; j < MAX_NUMBER; j++) {
            if (e[j] == i) {
                printf("%2d, ", j);
            }
        }
        printf("\n");
    }
}

TEST_CASE("test gamesSolutionSieve()")
{
    SUBCASE("game 2")
    {
        int *e = doSieve(game2SieveFor);
        print(e);
        CHECK(e[0] == 0);
        CHECK(e[1] == 1);
        CHECK(e[2] == 2);
        CHECK(e[3] == 3);
        CHECK(e[4] == 1);
        CHECK(e[5] == 4);
        CHECK(e[6] == 3);
        CHECK(e[7] == 2);
        CHECK(e[8] == 1);
        CHECK(e[9] == 4);
        delete[] e;
    }
    SUBCASE("game 3")
    {
        int *e = doSieve(game3SieveFor);
        print(e);
        CHECK(e[0] == 0);
        CHECK(e[1] == 0);
        CHECK(e[2] == 0);
        CHECK(e[3] == 1);
        CHECK(e[4] == 0);
        CHECK(e[5] == 2);
        CHECK(e[6] == 1);
        CHECK(e[7] == 0);
        CHECK(e[8] == 2);
        CHECK(e[9] == 1);
        delete[] e;
    }
}
