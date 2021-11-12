add_lib(common_gcd_lcm gcd_lcm.c gcd_lcm.h)
add_lib(common_fraction fraction.c fraction.h)
add_test(common common_test.cpp)
target_link_libraries(common_test common_gcd_lcm common_fraction)
