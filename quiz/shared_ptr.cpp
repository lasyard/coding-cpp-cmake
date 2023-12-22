#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <memory>
#include <string>

std::shared_ptr<std::string> use_string(std::shared_ptr<std::string> str, long *cnt)
{
    *cnt = str.use_count();
    return std::make_shared<std::string>(*str);
}

TEST_CASE("test_shared_ptr")
{
    long cnt;
    auto ptr = std::make_shared<std::string>("abcd");
    CHECK(ptr.use_count() == 1L);
    auto ptr1 = use_string(ptr, &cnt);
    CHECK(cnt == 2L);
    CHECK(ptr.use_count() == 1L);
    CHECK(ptr1.use_count() == 1L);
    ptr.reset();
    CHECK(ptr.use_count() == 0L);
    CHECK(ptr1.use_count() == 1L);
    ptr1.reset();
    CHECK(ptr.use_count() == 0L);
    CHECK(ptr1.use_count() == 0L);
}
