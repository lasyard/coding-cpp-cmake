/*
求解一道逻辑推理题。

请回答下面 10 个问题：

1. 第一个答案是 b 的问题是哪一个？
    (a) 2; (b) 3; (c) 4; (d) 5; (e) 6
2. 唯一的连续两个具有相同答案的问题是：
    (a) 2, 3; (b) 3, 4; (c) 4, 5; (d) 5, 6; (e) 6, 7
3. 本问题答案和哪一个问题的答案相同？
    (a) 1; (b) 2; (c) 4; (d) 7; (e) 6
4. 答案是 a 的问题的个数是：
    (a) 0; (b) 1; (c) 2; (d) 3; (e) 4
5. 本问题答案和哪一个问题的答案相同？
    (a) 10; (b) 9; (c) 8; (d) 7; (e) 6
6. 答案是 a 的问题的个数和答案是什么的问题的个数相同？
    (a) b; (b) c; (c) d; (d) e; (e) 以上都不是
7. 按照字母顺序，本问题的答案和下一个问题的答案相差几个字母？
    (a) 4; (b) 3; (c) 2; (d) 1; (e) 0（例如：a 和 b 相差一个字母）
8. 答案是元音字母的问题的个数是：
    (a) 2; (b) 3; (c) 4; (d) 5; (e) 6（注：a 和 e 是元音字母）
9. 答案是辅音字母的问题的个数是：
    (a) 一个质数；(b) 一个阶乘数；(c) 一个平方数；(d) 一个立方数；(e) 5 的倍数
10. 本问题的答案是：
    (a) a; (b) b; (c) c; (d) d; (e) e
*/

#include <stdio.h>

int abs(int x)
{
    return x < 0 ? -x : x;
}

static int a3[6] = {0, 1, 2, 4, 7, 6};
static int ans[11];

static void search(int n)
{
    int i, f, t;
    if (n < 11) {
        for (ans[n] = 1; ans[n] <= 5; ans[n]++) {
            search(n + 1);
        }
        return;
    }
    /* 1 */
    for (i = 1; i < 11 && ans[i] != 2; i++)
        ;
    if (ans[1] + 1 != i) {
        return;
    }
    /* 2 */
    f = 0;
    for (i = 1; i < 10; i++) {
        if (ans[i] == ans[i + 1]) {
            f++;
        }
    }
    if (f != 1 || ans[ans[2] + 1] != ans[ans[2] + 2]) {
        return;
    }
    /* 3 */
    if (ans[a3[ans[3]]] != ans[3]) {
        return;
    }
    /* 4 */
    t = 0;
    for (i = 1; i < 11; i++) {
        if (ans[i] == 1) {
            t++;
        }
    }
    if (ans[4] - 1 != t) {
        return;
    }
    /* 5 */
    if (ans[11 - ans[5]] != ans[5]) {
        return;
    }
    /* 6 */
    if (ans[6] == 5) {
        f = 0;
        for (i = 1; i < 11; i++) {
            if (ans[i] == 2) {
                f++;
            }
        }
        if (f == t) {
            return;
        }
        f = 0;
        for (i = 1; i < 11; i++) {
            if (ans[i] == 3) {
                f++;
            }
        }
        if (f == t) {
            return;
        }
        f = 0;
        for (i = 1; i < 11; i++) {
            if (ans[i] == 4) {
                f++;
            }
        }
        if (f == t) {
            return;
        }
        f = 0;
        for (i = 1; i < 11; i++) {
            if (ans[i] == 5) {
                f++;
            }
        }
        if (f == t) {
            return;
        }
    } else {
        f = 0;
        for (i = 1; i < 11; i++) {
            if (ans[i] == ans[6] + 1) {
                f++;
            }
        }
        if (f != t) {
            return;
        }
    }
    /* 7 */
    if (abs(ans[8] - ans[7]) != 5 - ans[7]) {
        return;
    }
    /* 8 */
    f = 0;
    for (i = 1; i < 11; i++) {
        if (ans[i] == 5) {
            f++;
        }
    }
    f += t;
    if (ans[8] + 1 != f) {
        return;
    }
    /* 9 */
    f = 10 - f;
    if (ans[9] == 1) {
        if (f != 2 && f != 3 && f != 5 && f != 7) {
            return;
        }
    } else if (ans[9] == 2) {
        if (f != 1 && f != 2 && f != 6) {
            return;
        }
    } else if (ans[9] == 3) {
        if (f != 1 && f != 4 && f != 9) {
            return;
        }
    } else if (ans[9] == 4) {
        if (f != 1 && f != 8) {
            return;
        }
    } else {
        if (f % 5 != 0) {
            return;
        }
    }
    /* output */
    printf("The answer: ");
    for (i = 1; i < 11; i++) {
        printf("%c ", ans[i] + 96);
    }
    printf("\n");
}

int main(void)
{
    search(1);
    return 0;
}

/*
The answer: c d e b e e d c b a
*/
