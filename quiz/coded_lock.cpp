/**
 * See https://lasy.readthedocs.io/quiz/math/coded_lock.html
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iomanip>
#include <iostream>

class CodedLock
{
public:
    CodedLock(int m, int n, int codeBase);
    virtual ~CodedLock();

    int getKeyNum() const
    {
        return m_keyNum;
    }

    int getCodeNum() const
    {
        return m_codeNum;
    }

    int getCodesPerKey() const
    {
        return m_codesPerKey;
    }

    int **getKeys() const
    {
        return m_key;
    }

private:
    int m_codeBase;
    int m_codeNum;
    int m_keyNum;
    int m_codesPerKey;
    int **m_key;

    friend std::ostream &operator<<(std::ostream &os, const CodedLock &obj);
};

CodedLock::CodedLock(int m, int n, int codeBase)
{
    m_keyNum = m;
    m_codeBase = codeBase;
    m_key = new int *[m_keyNum];
    if (n == 1) {
        m_codeNum = 1;
        m_codesPerKey = 1;
        for (int i = 0; i < m_keyNum; i++) {
            m_key[i] = new int[m_codesPerKey];
            m_key[i][0] = m_codeBase;
        }
    } else if (n == m) {
        m_codeNum = m;
        m_codesPerKey = 1;
        for (int i = 0; i < m_keyNum; i++) {
            m_key[i] = new int[m_codesPerKey];
            m_key[i][0] = m_codeBase + i;
        }
    } else {
        CodedLock code1(m - 1, n - 1, m_codeBase);
        CodedLock code2(m - 1, n, m_codeBase + code1.m_codeNum);
        m_codeNum = code1.m_codeNum + code2.m_codeNum;
        // Here we have `code1.m_codesPerKey + code2.m_codesPerKey == code2.m_codeNum`
        m_codesPerKey = code2.m_codeNum;
        int i, j;
        for (i = 0; i < m_keyNum - 1; i++) {
            m_key[i] = new int[m_codesPerKey];
            for (j = 0; j < code1.m_codesPerKey; j++) {
                m_key[i][j] = code1.m_key[i][j];
            }
            for (; j < m_codesPerKey; j++) {
                m_key[i][j] = code2.m_key[i][j - code1.m_codesPerKey];
            }
        }
        m_key[i] = new int[m_codesPerKey];
        for (j = 0; j < m_codesPerKey; j++) {
            m_key[i][j] = code2.m_codeBase + j;
        }
    }
}

CodedLock::~CodedLock()
{
    for (int i = 0; i < m_keyNum; i++) {
        delete[] m_key[i];
    }
    delete[] m_key;
}

std::ostream &operator<<(std::ostream &os, const CodedLock &obj)
{
    int i, j;
    os << "Codes: " << std::endl;
    for (i = obj.m_codeBase; i < obj.m_codeBase + obj.m_codeNum; i++) {
        os << std::setw(5) << i;
    }
    os << std::endl;
    os << "Keys: " << std::endl;
    for (i = 0; i < obj.m_keyNum; i++) {
        for (j = 0; j < obj.m_codesPerKey; j++) {
            os << std::setw(5) << obj.m_key[i][j];
        }
        os << std::endl;
    }
    return os;
}

TEST_CASE("Test CodedLock.")
{
    for (int m = 1; m < 10; ++m) {
        int c = 1;
        for (int n = 1; n <= m; ++n) {
            if (n > 1 && m > n) {
                c = c * (m - n + 1);
            }
            if (n > 2) {
                c /= n - 1;
            }
            CodedLock l(m, n, 0);
            std::cout << l;
            CHECK(l.getKeyNum() == m);
            CHECK(l.getCodesPerKey() == c);
            CHECK(l.getCodeNum() == c * m / (m - n + 1));
        }
    }
}
