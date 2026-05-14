file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/$<CONFIG>/RUNEWALL)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/$<CONFIG>/RUNEWALL)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/$<CONFIG>/RUNEWALL)

add_library(runewall SHARED)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

target_sources(runewall PRIVATE ${SOURCES})
target_compile_definitions(runewall PRIVATE RUNEWALL_BUILD_DLL)
target_include_directories(runewall
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(runewall PUBLIC gaven)
target_include_directories(runewall PUBLIC
    ${cjson_SOURCE_DIR}
)