find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_subdirectory(frame)
add_subdirectory(text)
