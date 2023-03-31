project(core LANGUAGES C)

aux_source_directory(./src SL)
aux_source_directory(./inc HL)

add_library(core STATIC ${SL} ${HL})
add_library(lib::core ALIAS core)

target_include_directories(
        core
        PUBLIC ./inc
)
#message(${PROJECT_NAME})