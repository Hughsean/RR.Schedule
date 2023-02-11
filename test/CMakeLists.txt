project(test)
cmake_minimum_required(VERSION 3.0)
#test.1
add_executable(t test.cpp)
target_link_libraries(t lib.core lib.helper)
