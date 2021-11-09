#ifndef _TERM_LINUX_H_
#define _TERM_LINUX_H_

#ifdef __cplusplus
extern "C" {
#endif

enum Color { BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE };

void setTerm();
void resetTerm();

int getKey();

void moveCursorTo(int x, int y);
void setColor(enum Color color);
void setBackColor(enum Color color);
void hideCursor();
void showCursor();
void clearScreen();
void delToEnd();

#ifdef __cplusplus
}
#endif

#endif
