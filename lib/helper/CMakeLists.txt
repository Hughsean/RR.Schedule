project(helper LANGUAGES CXX)

aux_source_directory(./src SL)
aux_source_directory(./inc HL)
add_library(helper STATIC ${SL} ${HL})

add_library(lib::helper ALIAS helper)
#target_link_libraries(main PRIVATE fmt::fmt)
#find_package(jsoncpp CONFIG REQUIRED)
#find_library(libcore oscore ../)
#find_library(core core ../)
find_package(fmt CONFIG REQUIRED)
target_link_libraries(
        helper
        PRIVATE fmt::fmt
        PRIVATE lib::core
)
#target_link_directories(${PROJECT_NAME} PRIVATE jsoncpp)
target_include_directories(
        helper
        PRIVATE lib::core
        PUBLIC ./inc
        #        PRIVATE core
)