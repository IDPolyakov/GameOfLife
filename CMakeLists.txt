cmake_minimum_required(VERSION 3.31)
project(GameOfLife)

find_package(SDL2 CONFIG REQUIRED)

add_executable(GameOfLife
    GameOfLife.cpp
    game.cpp
)

target_include_directories(GameOfLife PRIVATE game.h)

target_link_libraries(GameOfLife PRIVATE SDL2::SDL2 SDL2::SDL2main)
