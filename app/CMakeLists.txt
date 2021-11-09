add_exe(txt2html txt2html.cpp)
copy_file(copy_cfg_file txt2html.txt)
add_dependencies(txt2html copy_cfg_file)
