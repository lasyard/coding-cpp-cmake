#include <stdbool.h>
#include <stdio.h>

static int m[][9] = {
    {8, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 3, 6, 0, 0, 0, 0, 0},
    {0, 7, 0, 0, 9, 0, 2, 0, 0},
    {0, 5, 0, 0, 0, 7, 0, 0, 0},
    {0, 0, 0, 0, 4, 5, 7, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 3, 0},
    {0, 0, 1, 0, 0, 0, 0, 6, 8},
    {0, 0, 8, 5, 0, 0, 0, 1, 0},
    {0, 9, 0, 0, 0, 0, 4, 0, 0},
};

static void print(int m[][9])
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", m[i][j]);
        }
        putchar('\n');
    }
}

static bool rowInclude(int m[][9], int i, int x)
{
    for (int j = 0; j < 9; j++) {
        if (m[i][j] == x) {
            return true;
        }
    }
    return false;
}

static bool colInclude(int m[][9], int j, int x)
{
    for (int i = 0; i < 9; i++) {
        if (m[i][j] == x) {
            return true;
        }
    }
    return false;
}

static bool sqrInclude(int m[][9], int i, int j, int x)
{
    int ii, jj;
    for (ii = i / 3 * 3; ii <= i / 3 * 3 + 2; ii++) {
        for (jj = j / 3 * 3; jj <= j / 3 * 3 + 2; jj++) {
            if (m[ii][jj] == x) {
                return true;
            }
        }
    }
    return false;
}

static void nextPos(int pos[2], int m[][9], int i, int j)
{
    do {
        j++;
        if (j == 9) {
            i++;
            j = 0;
        }
        if (i == 9) {
            pos[0] = pos[1] = -1;
            return;
        }
    } while (m[i][j] != 0);
    pos[0] = i;
    pos[1] = j;
}

static void solve(int m[][9], int i, int j)
{
    int n[2];
    nextPos(n, m, i, j);
    if (n[0] == -1) {
        print(m);
        return;
    }
    for (int num = 1; num <= 9; num++) {
        if (rowInclude(m, n[0], num) || colInclude(m, n[1], num) || sqrInclude(m, n[0], n[1], num)) {
            continue;
        }
        m[n[0]][n[1]] = num;
        solve(m, n[0], n[1]);
        m[n[0]][n[1]] = 0;
    }
}

int main(void)
{
    solve(m, 0, -1);
    return 0;
}
