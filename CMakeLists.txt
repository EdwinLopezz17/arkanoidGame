cmake_minimum_required(VERSION 4.2)
project(arkanoid)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
include_directories(includes)
FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/master.tar.gz
)

add_executable(arkanoid main.cpp
        src/Ball.cpp
        includes/Ball.h
        src/Paddle.cpp
        includes/Paddle.h)

FetchContent_MakeAvailable(raylib)

target_link_libraries(arkanoid raylib)
