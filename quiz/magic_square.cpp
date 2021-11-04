#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iomanip>
#include <iostream>

class MagicSquare
{
public:
    MagicSquare(int n)
    {
        if (n < 1 || n == 2 || n > 100) {
            throw std::runtime_error("Illegal number.");
        }
        m_number = n;
        m_square = new int[n * n];
        magic();
    }

    virtual ~MagicSquare()
    {
        delete[] m_square;
    }

    int &operator()(int i, int j)
    {
        return m_square[i * m_number + j];
    }

private:
    int m_number;
    int *m_square;

    void magic();
    void magic1();
    void magic2();
    void magic4();

    friend std::ostream &operator<<(std::ostream &os, const MagicSquare &s);
};

void MagicSquare::magic()
{
    if (m_number % 4 == 0) {
        magic4();
    } else if (m_number % 2 == 0) {
        magic2();
    } else {
        magic1();
    }
}

void MagicSquare::magic1()
{
    int n = m_number;
    int i, j, ii, jj;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            ii = (n - i + j + (n - 1) / 2) % n;
            jj = (n - i + n - j + (n - 1) / 2 - 1) % n;
            (*this)(i, j) = ii * n + jj + 1;
        }
    }
}

void MagicSquare::magic2()
{
    int n = m_number;
    int i, j, ii, jj;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i < n / 2) {
                if (j < n / 2) {
                    ii = ((n + j - i) % (n / 2) < (n + 2) / 4) ? i : n - 1 - i;
                    jj = ((n + i - j) % (n / 2) < (n + 2) / 4) ? j : n - 1 - j;
                } else {
                    ii = ((n + j + i) % (n / 2) < (n + 2) / 4) ? n - 1 - i : i;
                    jj = ((n + i + j + 1) % (n / 2) < (n + 2) / 4) ? j : n - 1 - j;
                }
            } else {
                if (j < n / 2) {
                    ii = ((n + j + i + 1) % (n / 2) < (n + 2) / 4) ? i : n - 1 - i;
                    jj = ((n + i + j) % (n / 2) < (n + 2) / 4) ? n - 1 - j : j;
                } else {
                    ii = ((n + j - i - 1) % (n / 2) < (n + 2) / 4) ? n - 1 - i : i;
                    jj = ((n + i - j - 1) % (n / 2) < (n + 2) / 4) ? n - 1 - j : j;
                }
            }
            (*this)(i, j) = ii * n + jj + 1;
        }
    }
}

void MagicSquare::magic4()
{
    int n = m_number;
    int i, j, ii, jj;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            ii = (n / 4 <= i && i < 3 * n / 4) ? n - 1 - j : j;
            jj = (n / 4 <= j && j < 3 * n / 4) ? n - 1 - i : i;
            (*this)(i, j) = ii * n + jj + 1;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const MagicSquare &s)
{
    int n = s.m_number;
    int *p = s.m_square;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j, ++p) {
            os << std::setw(4) << *p;
        }
        os << std::endl;
    }
    return os;
}

TEST_CASE("Test MagicSquare.")
{
    SUBCASE("n = 1")
    {
        MagicSquare s(1);
        std::cout << s;
        CHECK(s(0, 0) == 1);
    }
    SUBCASE("n = 2")
    {
        CHECK_THROWS_WITH_AS(MagicSquare(2), "Illegal number.", std::runtime_error);
    }
    SUBCASE("n = 3")
    {
        MagicSquare s(3);
        std::cout << s;
        CHECK(s(0, 0) == 4);
        CHECK(s(0, 1) == 9);
        CHECK(s(0, 2) == 2);
        CHECK(s(1, 0) == 3);
        CHECK(s(1, 1) == 5);
        CHECK(s(1, 2) == 7);
        CHECK(s(2, 0) == 8);
        CHECK(s(2, 1) == 1);
        CHECK(s(2, 2) == 6);
    }
    SUBCASE("n = 4")
    {
        MagicSquare s(4);
        std::cout << s;
        CHECK(s(0, 0) == 1);
        CHECK(s(0, 1) == 8);
        CHECK(s(0, 2) == 12);
        CHECK(s(0, 3) == 13);
        CHECK(s(1, 0) == 14);
        CHECK(s(1, 1) == 11);
        CHECK(s(1, 2) == 7);
        CHECK(s(1, 3) == 2);
        CHECK(s(2, 0) == 15);
        CHECK(s(2, 1) == 10);
        CHECK(s(2, 2) == 6);
        CHECK(s(2, 3) == 3);
        CHECK(s(3, 0) == 4);
        CHECK(s(3, 1) == 5);
        CHECK(s(3, 2) == 9);
        CHECK(s(3, 3) == 16);
    }
    SUBCASE("n = 6")
    {
        MagicSquare s(6);
        std::cout << s;
        for (int i = 0; i < 6; ++i) {
            int sum = 0;
            for (int j = 0; j < 6; ++j) {
                sum += s(i, j);
            }
            CHECK(sum == 111);
        }
        for (int i = 0; i < 6; ++i) {
            int sum = 0;
            for (int j = 0; j < 6; ++j) {
                sum += s(j, i);
            }
            CHECK(sum == 111);
        }
        int sum = 0;
        for (int i = 0; i < 6; ++i) {
            sum += s(i, i);
        }
        CHECK(sum == 111);
        sum = 0;
        for (int i = 0; i < 6; ++i) {
            sum += s(i, 5 - i);
        }
        CHECK(sum == 111);
    }
}
