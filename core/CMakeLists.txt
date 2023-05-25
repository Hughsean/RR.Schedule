project(core)


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
        core.h
)
add_library(lib::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(core PRIVATE inc)
target_include_directories(core PUBLIC .)