/**
 * 抓棋子
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "term_linux.h"

#define random(x) (rand() % (x))

#define HEIGHT    15
#define BASE_LINE (HEIGHT + 5)
#define COIN      "====="
#define SPACE     "     "
#define WIDTH     5
#define GAP       (WIDTH + 1)

struct game {
    void (*turn)(struct game *g);
    int columns;
    int total;
    int pos;
    int *num;
};

static void playerTurn(struct game *g);
static void computerTurn(struct game *g);

static void move(struct game *g, int dx)
{
    g->pos += dx + g->columns;
    g->pos %= g->columns;
    moveCursorTo(g->pos * GAP + WIDTH / 2 + 1, BASE_LINE);
}

static void updateNum(const struct game *g, int pos)
{
    moveCursorTo(pos * GAP + WIDTH / 2, BASE_LINE);
    printf("%2d", g->num[pos]);
    moveCursorTo(1, 2);
    setColor(RED);
    printf("Total: %3d", g->total);
    moveCursorTo(g->pos * GAP + WIDTH / 2 + 1, BASE_LINE);
}

static void put(struct game *g, int pos, int num)
{
    g->num[pos] += num;
    g->total += num;
    setColor(pos % 2 ? RED : GREEN);
    for (int i = BASE_LINE - 1 - g->num[pos] + num; i > BASE_LINE - 1 - g->num[pos]; i--) {
        moveCursorTo(pos * GAP + 1, i);
        puts(COIN);
    }
    updateNum(g, pos);
}

static void pick(struct game *g, int pos, int num)
{
    g->num[pos] -= num;
    g->total -= num;
    for (int i = BASE_LINE - g->num[pos] - num; i < BASE_LINE - g->num[pos]; i++) {
        moveCursorTo(pos * GAP + 1, i);
        puts(SPACE);
    }
    updateNum(g, pos);
}

static void computerWin()
{
    setColor(RED);
    moveCursorTo(1, BASE_LINE + 1);
    puts("You lose!");
}

static void playerWin()
{
    setColor(GREEN);
    moveCursorTo(1, BASE_LINE + 1);
    puts("You win!");
}

static void computerTurn(struct game *g)
{
    int verify = 0;
    for (int i = 0; i < g->columns; i++) {
        verify ^= g->num[i];
    }
    if (verify == 0) {
        int i = random(g->columns);
        while (g->num[i] == 0) {
            i = random(g->columns);
        }
        pick(g, i, random(g->num[i]) + 1);
    } else {
        int i;
        for (i = 0; i < g->columns && (verify ^ g->num[i]) >= g->num[i]; i++)
            ;
        pick(g, i, g->num[i] - (verify ^ g->num[i]));
    }
    g->turn = (g->total == 0) ? computerWin : playerTurn;
}

static void playerTurn(struct game *g)
{
    int num = g->num[g->pos];
    while (g->turn == playerTurn) {
        switch (getKey()) {
        case 0x1B:
            g->turn = computerWin;
            break;
        case 0x0A:
            if (g->num[g->pos] < num) {
                g->turn = (g->total == 0) ? playerWin : computerTurn;
            }
            break;
        case 0x1B5B41: /* up */
            if (g->num[g->pos] < num) {
                put(g, g->pos, 1);
            }
            break;
        case 0x1B5B42: /* down */
            if (g->num[g->pos] > 0) {
                pick(g, g->pos, 1);
            }
            break;
        case 0x1B5B43: /* right */
            if (g->num[g->pos] == num) {
                move(g, 1);
                num = g->num[g->pos];
            }
            break;
        case 0x1B5B44: /* left */
            if (g->num[g->pos] == num) {
                move(g, -1);
                num = g->num[g->pos];
            }
            break;
        default:
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    struct game game;
    game.columns = 5;
    if (argc == 2) {
        game.columns = atoi(argv[1]);
        if (game.columns < 3 || game.columns > 12) {
            fprintf(stderr, "The number of columns must be within 3 - 12.\n");
            return -1;
        }
    } else if (argc > 2) {
        fprintf(stderr, "Please input number of columns.\n");
        return -1;
    }
    srand(time(NULL));
    setTerm();
    game.num = malloc(game.columns * sizeof(int));
    if (game.num == NULL) {
        fprintf(stderr, "Cannot allocate memory!\n");
        return -1;
    }
    int k;
    do {
        clearScreen();
        for (int i = 0; i < game.columns; i++) {
            game.num[i] = 0;
        }
        game.total = 0;
        game.pos = 0;
        for (int i = 0; i < game.columns; i++) {
            put(&game, i, random(HEIGHT) + 1);
        }
        game.turn = playerTurn;
        while (game.turn == computerTurn || game.turn == playerTurn) {
            game.turn(&game);
        }
        game.turn(&game);
        setColor(WHITE);
        printf("Try again? (Y)");
    } while ((k = getKey()) == 0x0A || k == (int)'y' || k == (int)'Y');
    free(game.num);
    resetTerm();
    printf("\n");
    return 0;
}
