cmake_minimum_required(VERSION 3.0.0)
project(code-cpp VERSION 1.0.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_subdirectory(doctest)

include(doctest/scripts/cmake/doctest.cmake)

function(add_test target)
    set(test_executable_name ${target}_test)
    add_executable(${test_executable_name} ${ARGN})
    target_compile_features(${test_executable_name} PRIVATE cxx_std_17 c_std_17)
    target_link_libraries(${test_executable_name} doctest)
    # Here `ADD_LABELS` must be provided.
    doctest_discover_tests(${test_executable_name} ADD_LABELS 1)
endfunction()

add_subdirectory(quiz)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
