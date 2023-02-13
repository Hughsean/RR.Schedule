cmake_minimum_required(VERSION 3.0)
project(lib)

add_library(lib.core SHARED src/core.c)

add_library(lib.helper SHARED src/helper.cpp)
target_link_libraries(lib.helper fmt jsoncpp)

target_include_directories(lib.core PUBLIC ./inc)
target_include_directories(lib.helper PUBLIC ./inc)

