cmake_minimum_required(VERSION 3.31)
project(RayForge VERSION 0.1.0 LANGUAGES CXX)

# Enable CTest
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

message("CMAKE_BUILD_TYPE  ${CMAKE_BUILD_TYPE}")

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

set(RAYFORGE_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)

add_subdirectory(engine)

add_executable(RayForge main.cpp)

message("ENGINE_3RD_PARTY_DIR  ${ENGINE_3RD_PARTY_DIR}")

target_include_directories(RayForge
    PRIVATE ${RAYFORGE_PROJECT_DIR}/engine)

target_link_libraries(RayForge PRIVATE raylib)