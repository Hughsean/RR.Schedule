cmake_minimum_required(VERSION 3.23)
project(A_C_LIB)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
include_directories(inc)
#add_library(A_C_LIB_SO SHARED src/library.c)
add_library(A_C_LIB STATIC src/library.c)

enable_testing()

# test1

add_executable(mytest test/test.cpp)
target_link_libraries(mytest A_C_LIB)
add_test(COMMAND mytest)
#