cmake_minimum_required(VERSION 3.10)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(RuneWallDemoBuild)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(Dependencies.cmake)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/$<CONFIG>/DEMO)

add_subdirectory(runewall)

option(RUNEWALL_BUILD_DEMO "Build Demo" OFF)
if (RUNEWALL_BUILD_DEMO)
add_subdirectory(demo)
endif()