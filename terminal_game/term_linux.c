#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>

#include "term_linux.h"

static struct termios g_orig_term_attr;

void setTerm()
{
    struct termios term_attr;
    tcgetattr(fileno(stdin), &g_orig_term_attr);
    memcpy(&term_attr, &g_orig_term_attr, sizeof(struct termios));
    term_attr.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(fileno(stdin), TCSANOW, &term_attr);
}

void resetTerm()
{
    tcsetattr(fileno(stdin), TCSANOW, &g_orig_term_attr);
    printf("\x1B[m");
}

int getKey()
{
    int key = fgetc(stdin);
    if (key != 0x1B) {
        return key;
    }
    int flag = fcntl(fileno(stdin), F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(fileno(stdin), F_SETFL, flag);
    int k;
    while ((k = fgetc(stdin)) != EOF) {
        key = ((key << 8) | (k & 0x000000FF));
    }
    flag &= ~O_NONBLOCK;
    fcntl(fileno(stdin), F_SETFL, flag);
    return key;
}

void moveCursorTo(int x, int y)
{
    printf("\x1B[%d;%dH", y, x);
}

void setColor(enum Color color)
{
    printf("\x1B[%dm", 30 + color);
}

void setBackColor(enum Color color)
{
    printf("\x1B[%dm", 40 + color);
}

void hideCursor()
{
    printf("\x1B[?25l");
}

void showCursor()
{
    printf("\x1B[?25h");
}

void clearScreen()
{
    printf("\x1B[2J");
}

void delToEnd()
{
    printf("\x1B[K");
}
