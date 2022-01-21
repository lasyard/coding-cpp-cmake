cmake_minimum_required(VERSION 3.0.0)
project(code-cpp VERSION 1.0.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_subdirectory(doctest)

include(doctest/scripts/cmake/doctest.cmake)

function(target_common_settings target)
    target_compile_features(${target} PRIVATE cxx_std_17 c_std_17)
    target_compile_options(${target} PRIVATE -Werror -Wall -Wextra)
endfunction()

function(add_test target)
    set(test_executable_name ${target}_test)
    add_executable(${test_executable_name} ${ARGN})
    target_common_settings(${test_executable_name})
    target_link_libraries(${test_executable_name} doctest)
    # Here `ADD_LABELS` must be provided.
    doctest_discover_tests(${test_executable_name} ADD_LABELS 1)
endfunction()

function(add_exe target)
    add_executable(${target} ${ARGN})
    target_common_settings(${target})
endfunction()

function(add_lib target)
    add_library(${target})
    target_sources(${target} PRIVATE ${ARGN})
    target_common_settings(${target})
endfunction()

function(copy_file target file)
    set(SRC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${file})
    set(TARGET_FILE ${CMAKE_CURRENT_BINARY_DIR}/${file})
    add_custom_target(${target} DEPENDS ${TARGET_FILE})
    add_custom_command(
        OUTPUT ${TARGET_FILE}
        COMMAND ${CMAKE_COMMAND} -E copy ${SRC_FILE} ${TARGET_FILE}
        DEPENDS ${SRC_FILE}
    )
endfunction()

add_subdirectory(app)
add_subdirectory(common)
add_subdirectory(count24)
add_subdirectory(quiz)
add_subdirectory(terminal_game)
add_subdirectory(wx)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
