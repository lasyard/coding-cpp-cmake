#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>

struct move {
    int disk;
    int from;
    int to;
};

static void recursiveMoveDisk(int disk, int from, int to, struct move moves[], int *step)
{
    if (disk > 0) {
        int other = 3 - from - to;
        recursiveMoveDisk(disk - 1, from, other, moves, step);
        struct move *m = &moves[*step];
        m->disk = disk;
        m->from = from;
        m->to = to;
        ++(*step);
        recursiveMoveDisk(disk - 1, other, to, moves, step);
    }
}

struct move *hanoi(int num)
{
    assert(num < 16);
    int step = 0;
    struct move *moves = new struct move[1 << num];
    recursiveMoveDisk(num, 0, 1, moves, &step);
    moves[step].disk = 0;
    return moves;
}

void print(struct move *move)
{
    int step = 0;
    for (struct move *m = move; m->disk > 0; ++m, ++step) {
        printf("Step %04d: disk %02d from %1d to %1d.\n", step, m->disk, m->from, m->to);
    }
}

TEST_CASE("test hanoi()")
{
    SUBCASE("1 disk")
    {
        struct move *m = hanoi(1);
        print(m);
        CHECK(m[0].disk == 1);
        CHECK(m[0].from == 0);
        CHECK(m[0].to == 1);
        delete[] m;
    }
    SUBCASE("2 disk")
    {
        struct move *m = hanoi(2);
        print(m);
        CHECK(m[0].disk == 1);
        CHECK(m[0].from == 0);
        CHECK(m[0].to == 2);
        CHECK(m[1].disk == 2);
        CHECK(m[1].from == 0);
        CHECK(m[1].to == 1);
        CHECK(m[2].disk == 1);
        CHECK(m[2].from == 2);
        CHECK(m[2].to == 1);
        delete[] m;
    }
    SUBCASE("3 disk")
    {
        struct move *m = hanoi(3);
        print(m);
        CHECK(m[0].disk == 1);
        CHECK(m[0].from == 0);
        CHECK(m[0].to == 1);
        CHECK(m[1].disk == 2);
        CHECK(m[1].from == 0);
        CHECK(m[1].to == 2);
        CHECK(m[2].disk == 1);
        CHECK(m[2].from == 1);
        CHECK(m[2].to == 2);
        CHECK(m[3].disk == 3);
        CHECK(m[3].from == 0);
        CHECK(m[3].to == 1);
        CHECK(m[4].disk == 1);
        CHECK(m[4].from == 2);
        CHECK(m[4].to == 0);
        CHECK(m[5].disk == 2);
        CHECK(m[5].from == 2);
        CHECK(m[5].to == 1);
        CHECK(m[6].disk == 1);
        CHECK(m[6].from == 0);
        CHECK(m[6].to == 1);
        delete[] m;
    }
}
