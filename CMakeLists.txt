cmake_minimum_required(VERSION 3.0)
project(OS_Design)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
#set(CMAKE_BUILD_TYPE Debug)
#
#set(CMAKE_BUILD_TYPE Release)

include_directories(inc)

add_library(LIB SHARED src/core.c src/helper.c)
#add_library(HELPER_LIB STATIC inc/helper.h src/helper.c)
#aux_source_directory(src SRC_LIST)
# test
add_executable(test test/test.cpp)
target_link_libraries(test LIB)
# a
add_executable(t test/t.cpp)