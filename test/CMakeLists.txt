cmake_minimum_required(VERSION 3.0)
project(T)

set(PROGRAMESPATH ${PROJECT_SOURCE_DIR})
set(OUTPUTPATH ${PROJECT_SOURCE_DIR})

configure_file(
        ${PROJECT_SOURCE_DIR}/Config.h.in
        ${PROJECT_SOURCE_DIR}/Config.h
)

add_executable(T 
T.cpp
inc/program_h.h
        inc/log.h
        src/log.cpp
        src/program_h.cpp
)

target_include_directories(T PRIVATE inc)

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(
        T
        PRIVATE lib::core
        PRIVATE JsonCpp::JsonCpp
)