add_library(term_linux)
target_sources(term_linux PRIVATE term_linux.c term_linux.h)
target_compile_features(term_linux PRIVATE cxx_std_17 c_std_17)
target_compile_options(term_linux PRIVATE -Werror -Wall -Wextra)
add_exe(mine mine.c)
target_link_libraries(mine term_linux)
add_exe(pick pick.c)
target_link_libraries(pick term_linux)
add_exe(sokoban sokoban.c)
target_link_libraries(sokoban term_linux)
set(SRC_XSB_FILE ${CMAKE_CURRENT_SOURCE_DIR}/default.xsb)
set(TARGET_XSB_FILE ${CMAKE_CURRENT_BINARY_DIR}/default.xsb)
add_custom_target(copy_xsb DEPENDS ${TARGET_XSB_FILE})
add_custom_command(
    OUTPUT ${TARGET_XSB_FILE}
    COMMAND ${CMAKE_COMMAND} -E copy ${SRC_XSB_FILE} ${TARGET_XSB_FILE}
    DEPENDS ${SRC_XSB_FILE}
)
add_dependencies(sokoban copy_xsb)
