/* Runs for long time if the chessboard is larger. */

#include <stdio.h>

#define X_SIZE 8
#define Y_SIZE 4

static void moveFrom(int (*map)[X_SIZE], int xSize, int ySize, int x, int y, int *steps);

static void print(int (*map)[X_SIZE], int xSize, int ySize)
{
    static int count = 0;
    printf("Solution %3d:\n", count++);
    for (int i = 0; i < ySize; i++) {
        for (int j = 0; j < xSize; j++) {
            printf("%3d", map[i][j]);
        }
        printf("\n");
    }
}

static void moveTo(int (*map)[X_SIZE], int xSize, int ySize, int x, int y, int *steps)
{
    if (0 <= x && x < xSize && 0 <= y && y < ySize && map[y][x] == 0) {
        ++(*steps);
        map[y][x] = *steps;
        if (*steps == xSize * ySize) {
            print(map, xSize, ySize);
        } else {
            moveFrom(map, xSize, ySize, x, y, steps);
        }
        map[y][x] = 0;
        --(*steps);
    }
}

static void moveFrom(int (*map)[X_SIZE], int xSize, int ySize, int x, int y, int *steps)
{
    moveTo(map, xSize, ySize, x - 2, y - 1, steps);
    moveTo(map, xSize, ySize, x - 2, y + 1, steps);
    moveTo(map, xSize, ySize, x - 1, y + 2, steps);
    moveTo(map, xSize, ySize, x + 1, y + 2, steps);
    moveTo(map, xSize, ySize, x + 2, y + 1, steps);
    moveTo(map, xSize, ySize, x + 2, y - 1, steps);
    moveTo(map, xSize, ySize, x + 1, y - 2, steps);
    moveTo(map, xSize, ySize, x - 1, y - 2, steps);
}

int main(void)
{
    int map[Y_SIZE][X_SIZE];
    for (int i = 0; i < Y_SIZE; i++) {
        for (int j = 0; j < X_SIZE; j++) {
            map[i][j] = 0;
        }
    }
    int steps = 1;
    map[0][0] = steps;
    printf("Searching...\n");
    moveFrom(map, X_SIZE, Y_SIZE, 0, 0, &steps);
    return 0;
}
