add_exe(txt2html txt2html.cpp)
copy_file(txt2html.txt)
target_sources(txt2html PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/txt2html.txt)
