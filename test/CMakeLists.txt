cmake_minimum_required(VERSION 3.0)
project(test)

add_executable(test test.cpp)
#test.1

find_package(jsoncpp CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(
        test
        PRIVATE lib::core
        PRIVATE lib::helper
        #        PRIVATE core
        PRIVATE fmt::fmt
        PRIVATE JsonCpp::JsonCpp
)
