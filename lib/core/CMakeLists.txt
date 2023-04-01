project(core LANGUAGES C)

#aux_source_directory(./src SL)
#aux_source_directory(./inc HL)

add_library(
        core SHARED
        inc/core.h
        inc/datastruct.h
        src/core.c
        inc/global_define.h)

add_library(lib::core ALIAS core)

target_include_directories(
        core
        PUBLIC ./inc
)
#message(${PROJECT_NAME})