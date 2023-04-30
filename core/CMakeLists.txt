project(core LANGUAGES C)


add_library(
        ${PROJECT_NAME}
        inc/global_define.h
        inc/process.h
        inc/cpu.h
        inc/kernel.h
        src/kernel.c
        src/cpu.c
        src/process.c
        inc/io.h
        src/io.c
        pub/core.h
)

add_library(lib::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
        core
        PUBLIC ./pub
        PRIVATE ./inc
)