cmake_minimum_required(VERSION 3.0)
project(OS_Design)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

#set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_BUILD_TYPE Release)
include_directories(inc)

add_library(LIB_CORE SHARED src/core.c)

add_library(LIB_HELPER STATIC src/helper.cpp)
target_link_libraries(LIB_HELPER fmt)

# test
add_executable(test test/test.cpp)
target_link_libraries(test LIB_CORE LIB_HELPER)
# a
add_executable(t test/t.c)