cmake_minimum_required(VERSION 3.0)
project(T)

add_executable(T1 t1.cpp)

find_package(jsoncpp CONFIG REQUIRED)

target_link_libraries(
        T1
        PRIVATE lib::core
        PRIVATE lib::helper
        PRIVATE JsonCpp::JsonCpp
)