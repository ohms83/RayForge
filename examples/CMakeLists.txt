add_executable(example-01 example-01.cpp)

target_include_directories(example-01
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(example-01
    PRIVATE RayForge)