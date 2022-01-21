find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})
add_executable(my_app
    my_app.cpp my_app.h
)
target_link_libraries(my_app ${wxWidgets_LIBRARIES})
