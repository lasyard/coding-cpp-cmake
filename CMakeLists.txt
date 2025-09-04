cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_OSX_SYSROOT /Library/Developer/CommandLineTools/SDKs/MacOSX12.sdk)
project(code-cpp VERSION 1.0.0 LANGUAGES C CXX)

include(cmake-common/functions.cmake)

using_doctest(doctest)

add_subdirectory(app)
add_subdirectory(common)
add_subdirectory(count24)
add_subdirectory(quiz)
add_subdirectory(terminal_game)

find_package(wxWidgets QUIET)
if(wxWidgets_FOUND)
    add_subdirectory(wx)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
