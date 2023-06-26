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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnonnull"
    CHECK((static_cast<NullObj *>(nullptr))->get() == nullptr);
#pragma GCC diagnostic pop
}
