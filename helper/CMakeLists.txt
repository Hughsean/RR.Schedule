project(helper LANGUAGES CXX)

#aux_source_directory(./src SL)
#aux_source_directory(./inc HL)

add_library(
        helper
        inc/process_h.h
        inc/log.h
        src/log.cpp
        src/process_h.cpp
)
add_library(lib::helper ALIAS helper)

find_package(jsoncpp CONFIG REQUIRED)

target_link_libraries(
        helper
        PRIVATE JsonCpp::JsonCpp
        PRIVATE lib::core
)

target_include_directories(
        helper
        PRIVATE lib::core
        PUBLIC inc
)