project(core)


add_library(
        ${PROJECT_NAME}
        inc/cpu.h
        src/cpu.c
        inc/process.h
        src/process.c
        inc/kernel.h
        src/kernel.c
        inc/io.h
        src/io.c
        interface/inc/interface.h
        interface/interface.c
        inc/config.h
)
add_library(lib::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(core PRIVATE inc)
target_include_directories(core PUBLIC interface/inc)