add_subdirectory(${RAYFORGE_3RD_PARTY_DIR})

# Add engine modules
add_subdirectory(${RAYFORGE_MODULES_DIR}/core)
add_subdirectory(${RAYFORGE_MODULES_DIR}/debug)

add_library(RayForge STATIC Stub.cpp)

target_include_directories(RayForge
    PUBLIC ${RAYFORGE_MODULES_DIR})

target_link_libraries(RayForge
    PRIVATE raylib
    PRIVATE rf-core
    PRIVATE rf-debug)