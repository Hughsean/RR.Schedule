cmake_minimum_required(VERSION 3.0)
project(T)

add_executable(T T.cpp)

find_package(jsoncpp CONFIG REQUIRED)

target_link_libraries(
        T
        PRIVATE lib::core
        PRIVATE lib::helper
        PRIVATE JsonCpp::JsonCpp
)