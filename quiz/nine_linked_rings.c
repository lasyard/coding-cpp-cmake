/**
 * See https://lasy.readthedocs.io/quiz/math/nine_linked_rings.html
 */

#include <stdio.h>

#define RINGS 9

static void print(int pos[])
{
    for (int i = 0; i < RINGS; i++) {
        printf("%2d", pos[i]);
    }
    printf("\n");
}

static void moveRing(int pos[], int ring, int to)
{
    static int steps = 0;
    steps++;
    pos[ring] = to;
    printf("Step %3d: Ring %2d %-5s->", steps, ring, to == 1 ? "Up" : "Down");
    print(pos);
}

static void moveAllRings(int pos[], int ring, int to)
{
    if (to == 1 && ring >= 1) {
        moveAllRings(pos, ring - 1, 1);
    }
    if (ring >= 2) {
        moveAllRings(pos, ring - 2, 0);
    }
    moveRing(pos, ring, to);
    if (ring >= 2) {
        moveAllRings(pos, ring - 2, 1);
    }
    if (to == 0 && ring >= 1) {
        moveAllRings(pos, ring - 1, 0);
    }
}

int main(void)
{
    int pos[RINGS];
    for (int i = 0; i < RINGS; i++) {
        pos[i] = 1;
    }
    moveAllRings(pos, RINGS - 1, 0);
    return 0;
}
