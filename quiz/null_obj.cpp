#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iostream>

class NullObj
{
public:
    NullObj *get()
    {
        return this;
    }
};

TEST_CASE("test_null_obj")
{
    CHECK((static_cast<NullObj *>(nullptr))->get() == nullptr);
}
