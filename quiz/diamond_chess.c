#include <stdbool.h>
#include <stdio.h>

struct move {
    int x1, y1;
    int x2, y2;
};

static struct move moveStack[32];
static int top = 0;

static int map[7][7] = {
    {2, 2, 1, 1, 1, 2, 2},
    {2, 2, 1, 1, 1, 2, 2},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {2, 2, 1, 1, 1, 2, 2},
    {2, 2, 1, 1, 1, 2, 2},
};

static bool valid(int x, int y)
{
    return 0 <= x && x < 7 && 0 <= y && y < 7;
}

static bool occupied(int x, int y)
{
    return valid(x, y) && map[y][x] == 1;
}

static bool vacant(int x, int y)
{
    return valid(x, y) && map[y][x] == 0;
}

static void printMove(const struct move *j)
{
    printf("(%d, %d) -> (%d, %d)", j->x1, j->y1, j->x2, j->y2);
}

static void print()
{
    int moves = 1;
    for (int i = 1; i < top; i++) {
        if (moveStack[top].x1 != moveStack[top - 1].x2 || moveStack[top].y1 != moveStack[top - 1].y2)
            moves++;
    }
    printf("%d moves:", moves);
    for (int i = 0; i < top; i++) {
        if (i % 3 == 0) {
            printf("\n");
        } else {
            printf(" ");
        }
        printMove(&moveStack[i]);
    }
    printf("\n");
}

static void pushMove(int x1, int y1, int x2, int y2)
{
    map[y1][x1] = 0;
    map[(y1 + y2) / 2][(x1 + x2) / 2] = 0;
    map[y2][x2] = 1;
    moveStack[top].x1 = x1;
    moveStack[top].y1 = y1;
    moveStack[top].x2 = x2;
    moveStack[top].y2 = y2;
    top++;
}

static void popMove()
{
    int x1, y1, x2, y2;
    top--;
    x1 = moveStack[top].x1;
    y1 = moveStack[top].y1;
    x2 = moveStack[top].x2;
    y2 = moveStack[top].y2;
    map[y2][x2] = 0;
    map[(y1 + y2) / 2][(x1 + x2) / 2] = 1;
    map[y1][x1] = 1;
}

static bool move(int x1, int y1, int x2, int y2)
{
    if (!vacant(x2, y2) || !occupied((x1 + x2) / 2, (y1 + y2) / 2)) {
        return false;
    }
    bool ok = false;
    pushMove(x1, y1, x2, y2);
    if (top == 31) {
        if (map[3][3] == 1) {
            print();
            ok = true;
        }
    } else {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                if (occupied(i, j)) {
                    ok = ok || move(i, j, i - 2, j);
                    ok = ok || move(i, j, i, j - 2);
                    ok = ok || move(i, j, i + 2, j);
                    ok = ok || move(i, j, i, j + 2);
                }
            }
        }
    }
    popMove();
    return ok;
}

int main(void)
{
    if (!move(1, 3, 3, 3)) {
        printf("Failed!\n");
    }
    return 0;
}

/*
31 moves:
(1, 3) -> (3, 3) (2, 1) -> (2, 3) (0, 2) -> (2, 2)
(0, 4) -> (0, 2) (2, 3) -> (2, 1) (2, 0) -> (2, 2)
(2, 4) -> (0, 4) (2, 6) -> (2, 4) (3, 2) -> (1, 2)
(0, 2) -> (2, 2) (3, 0) -> (3, 2) (3, 2) -> (1, 2)
(3, 4) -> (1, 4) (0, 4) -> (2, 4) (3, 6) -> (3, 4)
(3, 4) -> (1, 4) (5, 2) -> (3, 2) (4, 0) -> (4, 2)
(4, 2) -> (2, 2) (1, 2) -> (3, 2) (3, 2) -> (3, 4)
(4, 4) -> (2, 4) (1, 4) -> (3, 4) (4, 6) -> (4, 4)
(4, 3) -> (4, 5) (6, 4) -> (4, 4) (3, 4) -> (5, 4)
(6, 2) -> (6, 4) (6, 4) -> (4, 4) (4, 5) -> (4, 3)
(5, 3) -> (3, 3)
*/
