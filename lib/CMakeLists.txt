#cmake_minimum_required(VERSION 3.0)
#project(lib)
#
#include_directories(inc)
#
#add_library(lib.core SHARED src/core.c)
#add_library(lib.helper SHARED src/helper.cpp)
#
#find_package(fmt CONFIG REQUIRED)
#find_package(jsoncpp CONFIG REQUIRED)
#
#target_link_libraries(lib.helper PRIVATE fmt::fmt)
#target_link_libraries(lib.helper PRIVATE JsonCpp::JsonCpp lib.core)
add_subdirectory(./core)
add_subdirectory(./helper)
#target_include_directories(lib.core PUBLIC ./inc)
#target_include_directories(lib.helper PUBLIC ./inc)

