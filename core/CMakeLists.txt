project(core LANGUAGES C)

#aux_source_directory(./src SL)
#aux_source_directory(./inc HL)

add_library(
        core STATIC
        inc/global_define.h
        inc/process.h
        inc/cpu.h
        inc/kernel.h
        src/kernel.c
        src/cpu.c
        src/process.c
#        pub/preinclude.h
)

add_library(lib::core ALIAS core)

target_include_directories(
        core
        PUBLIC ./pub
        PRIVATE ./inc
)
#message(${PROJECT_NAME})