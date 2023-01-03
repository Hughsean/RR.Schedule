cmake_minimum_required(VERSION 3.23)
project(A_C_LIB)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)


include_directories(inc)
add_library(A_C_LIB STATIC src/library.c)

# test
add_executable(test test/test.cpp)
target_link_libraries(test A_C_LIB)

# a
add_executable(t test/t.cpp)