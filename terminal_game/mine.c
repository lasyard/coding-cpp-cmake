#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "term_linux.h"

#define random(x) (rand() % (x))

#define MAP_Y       20
#define MAP_X       40
#define MINE_NUMBER 120

#define BASE_LINE (MAP_Y + 4)

struct cell {
    int num;
    bool mine;
    bool opened;
    bool marked;
    bool exploded;
};

struct game {
    struct cell map[MAP_X][MAP_Y];
    int mineLeft;
    int openCount;
    bool autoMark;
    bool dead;
};

typedef bool CellFun(struct game *, int, int); /* used by aroundCell() */

static bool openAround(struct game *g, int x, int y);
static bool autoMark(struct game *g, int x, int y);

static bool isValid(int x, int y)
{
    return 0 <= x && x < MAP_X && 0 <= y && y < MAP_Y;
}

static void output(char symbol, enum Color backcolor, enum Color color, int x, int y)
{
    setBackColor(backcolor);
    setColor(color);
    moveCursorTo(x + 1, y + 1);
    putchar(symbol);
}

static void showCoveredCell(int x, int y)
{
    output(' ', WHITE, BLUE, x, y);
}

static void showOpenedCell(int x, int y, int num)
{
    static enum Color color[9] = {BLUE, WHITE, CYAN, GREEN, YELLOW, RED, PURPLE, PURPLE, PURPLE};
    if (num == 0) {
        output(' ', BLUE, color[num], x, y);
    } else {
        output((char)(0x30 | num), BLUE, color[num], x, y);
    }
}

static void showMarkedCell(int x, int y)
{
    output('P', YELLOW, BLUE, x, y);
}

static void showExplodedCell(int x, int y)
{
    output('X', RED, GREEN, x, y);
}

static void updateMineNum(int num)
{
    moveCursorTo(1, BASE_LINE - 2);
    setBackColor(BLACK);
    setColor(RED);
    printf("Bomb left: %3d", num);
}

static void showAutoMark(int mark)
{
    moveCursorTo(60, BASE_LINE - 2);
    setBackColor(BLACK);
    setColor(YELLOW);
    printf("%c", mark ? 'A' : ' ');
}

static void failed()
{
    moveCursorTo(20, BASE_LINE - 2);
    setBackColor(BLACK);
    setColor(RED);
    puts("You have been bombed!");
}

static void victory()
{
    moveCursorTo(20, BASE_LINE - 2);
    setBackColor(BLACK);
    setColor(GREEN);
    puts("Mission accomplished!");
}

static bool marked(struct game *g, int x, int y)
{
    return g->map[x][y].marked;
}

static bool covered(struct game *g, int x, int y)
{
    return !g->map[x][y].opened && !g->map[x][y].marked;
}

static bool addMineNumber(struct game *g, int x, int y)
{
    if (!g->map[x][y].mine) {
        g->map[x][y].num++;
    }
    return false;
}

static int aroundCell(struct game *g, int x, int y, CellFun *fun)
{
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (isValid(x + i, y + j) && fun(g, x + i, y + j)) {
                count++;
            }
        }
    }
    return count;
}

static void initMap(struct game *g)
{
    for (int i = 0; i < MAP_X; i++) {
        for (int j = 0; j < MAP_Y; j++) {
            g->map[i][j].num = 0;
            g->map[i][j].mine = 0;
            g->map[i][j].opened = 0;
            g->map[i][j].marked = 0;
            g->map[i][j].exploded = 0;
            showCoveredCell(i, j);
        }
    }
}

static void setMap(struct game *g)
{
    initMap(g);
    for (int i = 0; i < MINE_NUMBER;) {
        int x = random(MAP_X);
        int y = random(MAP_Y);
        if (!g->map[x][y].mine) {
            g->map[x][y].mine = true;
            aroundCell(g, x, y, addMineNumber);
            i++;
        }
    }
    g->openCount = 0;
    g->mineLeft = MINE_NUMBER;
    updateMineNum(g->mineLeft);
}

static void initGame(struct game *g)
{
    setBackColor(BLACK);
    setColor(WHITE);
    clearScreen();
    moveCursorTo(1, BASE_LINE);
    printf("ESC=Quit | Enter=Open | Insert=Mark | Delete=Erase Mark | A=Auto");
    setMap(g);
    g->autoMark = false;
    showAutoMark(g->autoMark);
    g->dead = false;
}

static bool openCell(struct game *g, int x, int y)
{
    if (covered(g, x, y)) {
        if (g->map[x][y].mine) {
            g->map[x][y].exploded = true;
            showExplodedCell(x, y);
            g->dead = true;
        } else {
            g->map[x][y].opened = true;
            showOpenedCell(x, y, g->map[x][y].num);
            openAround(g, x, y);
            if (g->autoMark) {
                aroundCell(g, x, y, autoMark);
            }
            g->openCount++;
        }
    }
    return false;
}

static bool openAround(struct game *g, int x, int y)
{
    if (g->map[x][y].opened) {
        if (g->map[x][y].num == aroundCell(g, x, y, marked)) {
            aroundCell(g, x, y, openCell);
        }
    }
    return false;
}

static bool markCell(struct game *g, int x, int y)
{
    if (covered(g, x, y)) {
        g->mineLeft--;
        updateMineNum(g->mineLeft);
        g->map[x][y].marked = true;
        showMarkedCell(x, y);
        if (g->autoMark) {
            aroundCell(g, x, y, openAround);
            aroundCell(g, x, y, autoMark);
        }
    }
    return false;
}

static void eraseMark(struct game *g, int x, int y)
{
    if (g->map[x][y].marked) {
        g->mineLeft++;
        updateMineNum(g->mineLeft);
        g->map[x][y].marked = false;
        showCoveredCell(x, y);
    }
}

static bool autoMark(struct game *g, int x, int y)
{
    if (g->map[x][y].opened) {
        int a = aroundCell(g, x, y, marked);
        int b = aroundCell(g, x, y, covered);
        if (g->map[x][y].num - a == b)
            aroundCell(g, x, y, markCell);
    }
    return false;
}

int main(void)
{
    srand(time(NULL));
    setTerm();
    struct game game;
    while (true) {
        initGame(&game);
        int x = MAP_X / 2;
        int y = MAP_Y / 2;
        moveCursorTo(x + 1, y + 1);
        bool quit = false;
        while (!quit && !game.dead && game.openCount < MAP_Y * MAP_X - MINE_NUMBER) {
            switch (getKey()) {
            case 0x1B:
                quit = true;
                break;
            case 0x0A:
                if (covered(&game, x, y)) {
                    openCell(&game, x, y);
                } else {
                    openAround(&game, x, y);
                }
                break;
            case 0x1B5B41: /* up */
                if (y > 0) {
                    y--;
                }
                break;
            case 0x1B5B42: /* down */
                if (y < MAP_Y - 1) {
                    y++;
                }
                break;
            case 0x1B5B43: /* right */
                if (x < MAP_X - 1) {
                    x++;
                }
                break;
            case 0x1B5B44: /* left */
                if (x > 0) {
                    x--;
                }
                break;
            case 0x1B5B327E: /* insert */
                markCell(&game, x, y);
                break;
            case 0x1B5B337E: /* delete */
                eraseMark(&game, x, y);
                break;
            case 'a':
            case 'A':
                game.autoMark = !game.autoMark;
                showAutoMark(game.autoMark);
                break;
            default:
                break;
            }
            moveCursorTo(x + 1, y + 1);
        }
        if (!quit) {
            if (game.dead) {
                failed();
            } else {
                victory();
            }
        }
        moveCursorTo(1, BASE_LINE);
        setBackColor(BLACK);
        setColor(WHITE);
        delToEnd();
        puts("ESC to quit. Any key else to play again.");
        if (getKey() == 0x1B) {
            break;
        }
    }
    resetTerm();
    return 0;
}
