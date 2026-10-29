set(TARGET_NAME rf-core)

file(GLOB_RECURSE RF_CORE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(${TARGET_NAME} STATIC ${RF_CORE_SOURCES})

target_include_directories(${TARGET_NAME}
    PRIVATE ${RAYFORGE_MODULES_DIR})

target_link_libraries(${TARGET_NAME}
    PRIVATE raylib
    PRIVATE rf-debug
)