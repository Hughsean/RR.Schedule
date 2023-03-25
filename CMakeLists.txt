project(OS.CD)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)
add_subdirectory(./lib)
add_subdirectory(./test)
