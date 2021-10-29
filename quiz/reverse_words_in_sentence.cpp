#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <cstring>

static void reverseString(char *begin, char *end)
{
    char *p, *q;
    for (p = begin, q = end - 1; p < q; p++, q--) {
        char tmp = *p;
        *p = *q;
        *q = tmp;
    }
}

void reverseWordsInSentence(char *text)
{
    if (text == nullptr) {
        return;
    }
    int len = strlen(text);
    reverseString(text, text + len);
    for (char *p = text, *q; *p != '\0';) {
        if (*p == ' ') {
            p++;
            continue;
        }
        for (q = p + 1; *q != '\0' && *q != ' '; q++)
            ;
        reverseString(p, q);
        if (*q == '\0') {
            break;
        }
        p = q + 1;
    }
}

TEST_CASE("Test reverseWordsInSentence()")
{
    SUBCASE("null")
    {
        reverseWordsInSentence(nullptr);
    }
    SUBCASE("empty")
    {
        char text[] = "";
        reverseWordsInSentence(text);
        CHECK(strcmp(text, "") == 0);
    }
    SUBCASE("spaces")
    {
        char text[] = "     ";
        reverseWordsInSentence(text);
        CHECK(strcmp(text, "     ") == 0);
    }
    SUBCASE("I_am_superman")
    {
        char text[] = "I am superman. ";
        reverseWordsInSentence(text);
        CHECK(strcmp(text, " superman. am I") == 0);
    }
}
