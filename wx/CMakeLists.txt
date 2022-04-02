find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})
add_exe(my_app
    my_app.cpp
    my_frame.cpp
)
target_link_libraries(my_app ${wxWidgets_LIBRARIES})
