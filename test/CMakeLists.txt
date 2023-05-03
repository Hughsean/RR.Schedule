cmake_minimum_required(VERSION 3.0)
project(T)

add_executable(T1 t1.cpp)
add_executable(T2 t2.cpp)

find_package(jsoncpp CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(
        T1
        PRIVATE lib::core
        PRIVATE lib::helper
        PRIVATE fmt::fmt
        PRIVATE JsonCpp::JsonCpp
)
target_link_libraries(
        T2
        PRIVATE lib::core
        PRIVATE lib::helper
        PRIVATE fmt::fmt
        PRIVATE JsonCpp::JsonCpp
)