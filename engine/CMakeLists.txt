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

target_compile_definitions(RayForge PUBLIC
    RF_PROJECT_PATH="${RAYFORGE_PROJECT_DIR}"
    RF_ASSETS_DIR="${RAYFORGE_PROJECT_DIR}/assets"
    RF_GENERATED_ASSETS_DIR="${RAYFORGE_PROJECT_DIR}/gen"
    $<$<CONFIG:Debug>:RF_BUILD_DEBUG>
    $<$<CONFIG:RelWithDebInfo>:RF_BUILD_RELWITHDEBINFO>
    $<$<CONFIG:Release>:RF_BUILD_RELEASE>
)