cmake_minimum_required(VERSION 3.0)
project(lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

include_directories(inc)

add_library(lib.core SHARED src/core.c)

add_library(lib.helper SHARED src/helper.cpp)
target_link_libraries(lib.helper fmt)

target_include_directories(lib.core PUBLIC ./inc)
target_include_directories(lib.helper PUBLIC ./inc)

