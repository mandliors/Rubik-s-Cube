cmake_minimum_required(VERSION 3.11)
project(RubixCube)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

# dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
include(FetchContent)
    FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    endif()
endif()

# project
add_executable(${PROJECT_NAME} ${SOURCES})

target_sources(${PROJECT_NAME} PRIVATE
    src/Main.cpp
    src/Cube/Cube.cpp
    src/Piece/Piece.cpp
)
include_directories(${PROJECT_NAME} PRIVATE
    src
)
target_link_libraries(${PROJECT_NAME}
    raylib
)
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
)
target_compile_options(${PROJECT_NAME} PRIVATE
    -fsanitize=address
    -fno-omit-frame-pointer
)
target_link_options(${PROJECT_NAME} PRIVATE
    -fsanitize=address
)