#include <stdio.h>

#define QUEENS 8

static void print(int pos[])
{
    static int count = 0;
    count++;
    printf("Solution %3d:\n", count);
    for (int i = 0; i < QUEENS; ++i) {
        for (int j = 0; j < QUEENS; ++j) {
            putchar(pos[i] == j ? 'O' : '+');
            putchar(' ');
        }
        putchar('\n');
    }
}

static void putQueenInLine(int pos[], int line)
{
    if (line < QUEENS) {
        for (int i = 0; i < QUEENS; i++) {
            int j;
            for (j = 0; j < line; j++) {
                if (i == pos[j] || i - pos[j] == line - j || pos[j] - i == line - j) {
                    break;
                }
            }
            if (j == line) {
                pos[line] = i;
                putQueenInLine(pos, line + 1);
            }
        }
    } else {
        print(pos);
    }
}

int main(void)
{
    int pos[QUEENS];
    putQueenInLine(pos, 0);
    return 0;
}
