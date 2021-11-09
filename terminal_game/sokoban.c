#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "term_linux.h"

#define BUF_SIZE 127

#define FLOOR 0x00000000
#define WALL  0x00000001
#define GOAL  0x00000002
#define BOX   0x00010000
#define MAN   0x00020000

struct level {
    int map_x, map_y;
    int **map;
    int count;
    int man_x, man_y;
};

static bool readLevel(struct level *lv, const char *file)
{
    lv->count = 0;
    lv->map_x = 0;
    lv->map_y = 0;
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        return false;
    }
    char buf[BUF_SIZE + 1];
    while (fgets(buf, BUF_SIZE, fp) != NULL) {
        int len;
        buf[BUF_SIZE] = '\0';
        len = strlen(buf);
        if (len > lv->map_x) {
            lv->map_x = len;
        }
        lv->map_y++;
    }
    lv->map = malloc(lv->map_y * sizeof(int *));
    if (lv->map == NULL) {
        return false;
    }
    rewind(fp);
    int i;
    for (i = 0; i < lv->map_y; i++) {
        lv->map[i] = malloc(lv->map_x * sizeof(int));
        if (lv->map[i] == NULL) {
            break;
        }
        memset(lv->map[i], 0, lv->map_x * sizeof(int));
        if (fgets(buf, BUF_SIZE, fp) == NULL) {
            break;
        }
        for (int j = 0; j < lv->map_x; j++) {
            char ch = buf[j];
            if (ch == '\0' || ch == '\r' || ch == '\n') {
                break;
            }
            switch (ch) {
            case '-':
            case ' ':
                lv->map[i][j] = FLOOR;
                break;
            case '#':
                lv->map[i][j] = WALL;
                break;
            case '$':
                lv->map[i][j] = BOX;
                lv->count++;
                break;
            case '.':
                lv->map[i][j] = GOAL;
                break;
            case '*':
                lv->map[i][j] = (BOX | GOAL);
                break;
            case '@':
                lv->map[i][j] = FLOOR;
                lv->man_x = j;
                lv->man_y = i;
                break;
            case '+':
                lv->map[i][j] = GOAL;
                lv->man_x = j;
                lv->man_y = i;
            default:
                break;
            }
        }
    }
    if (i < lv->map_y) {
        while (--i >= 0) {
            free(lv->map[i]);
        }
        return false;
    }
    fclose(fp);
    return true;
}

static void releaseLevel(struct level *lv)
{
    for (int i = 0; i < lv->map_y; i++) {
        free(lv->map[i]);
    }
    free(lv->map);
}

static bool isVictory(const struct level *lv)
{
    if (lv->count == 0) {
        moveCursorTo(0, lv->map_y + 1);
        printf("You are smart!\n");
        return true;
    }
    return false;
}

static void show(int x, int y, int type)
{
    moveCursorTo(x * 2 + 1, y + 1);
    switch (type) {
    case FLOOR:
        setBackColor(BLACK);
        puts("  ");
        break;
    case WALL:
        setBackColor(WHITE);
        puts("  ");
        break;
    case GOAL:
        setBackColor(BLUE);
        puts("  ");
        break;
    case BOX:
        setBackColor(RED);
        puts("  ");
        break;
    case BOX | GOAL:
        setBackColor(PURPLE);
        puts("  ");
        break;
    case MAN:
        setBackColor(GREEN);
        puts("  ");
        break;
    default:
        break;
    }
}

static void showLevel(const struct level *lv)
{
    for (int i = 0; i < lv->map_y; i++) {
        for (int j = 0; j < lv->map_x; j++) {
            show(j, i, lv->map[i][j]);
        }
    }
    show(lv->man_x, lv->man_y, MAN);
}

static bool moveBox(struct level *lv, int x, int y, int dx, int dy)
{
    int xx = x + dx;
    int yy = y + dy;
    if (lv->map[yy][xx] == WALL || (lv->map[yy][xx] & BOX) == BOX) {
        return false;
    }
    if (lv->map[y][x] == (BOX | GOAL)) {
        lv->count++;
    }
    lv->map[y][x] &= ~BOX;
    show(x, y, lv->map[y][x]);
    lv->map[yy][xx] |= BOX;
    show(xx, yy, lv->map[yy][xx]);
    if (lv->map[yy][xx] == (BOX | GOAL)) {
        lv->count--;
    }
    return true;
}

static bool moveMan(struct level *lv, int dx, int dy)
{
    int xx = lv->man_x + dx;
    int yy = lv->man_y + dy;
    if (lv->map[yy][xx] == WALL) {
        return false;
    }
    if ((lv->map[yy][xx] & BOX) == BOX && !moveBox(lv, xx, yy, dx, dy)) {
        return false;
    }
    show(lv->man_x, lv->man_y, lv->map[lv->man_y][lv->man_x]);
    lv->man_x = xx;
    lv->man_y = yy;
    show(lv->man_x, lv->man_y, MAN);
    return true;
}

int main(int argc, char *argv[])
{
    const char *file = "default.xsb";
    if (argc == 2) {
        file = argv[1];
    } else if (argc > 2) {
        fprintf(stderr, "Please input XSB file name.\n");
        return -1;
    }
    struct level level;
    if (!readLevel(&level, file)) {
        fprintf(stderr, "Error reading xsb file!\n");
        return -1;
    }
    setTerm();
    hideCursor();
    clearScreen();
    showLevel(&level);
    for (bool quit = false; !quit;) {
        switch (getKey()) {
        case 0x1B:
            quit = true;
            break;
        case 0x1B5B41: /* up */
            moveMan(&level, 0, -1);
            break;
        case 0x1B5B42: /* down */
            moveMan(&level, 0, 1);
            break;
        case 0x1B5B43: /* right */
            moveMan(&level, 1, 0);
            break;
        case 0x1B5B44: /* left */
            moveMan(&level, -1, 0);
            break;
        default:
            break;
        }
        if (isVictory(&level)) {
            quit = true;
        }
    }
    showCursor();
    resetTerm();
    releaseLevel(&level);
    return 0;
}
