#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <cstdlib>
#include <fstream>

#include "set_env_from_file.h"

#define FILE_NAME "set_env_from_file_test.dat"

TEST_CASE("Test set_env_from_file()")
{
    std::ofstream file(FILE_NAME);
    CHECK(file);
    file << "TEST_ENV=test_string" << std::endl;
    file.close();
    CHECK(set_env_from_file(FILE_NAME));
    const char *v = getenv("TEST_ENV");
    CHECK(v != NULL);
    CHECK(strcmp(v, "test_string") == 0);
    std::remove(FILE_NAME);
}
