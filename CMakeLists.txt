cmake_minimum_required(VERSION 3.25)
project(group18)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-lncurses")



        include_directories(.)

add_executable(group18
        Block.cpp
        Block.hpp
        Board.cpp
        Board.hpp
        Game.cpp
        Game.hpp
        Main.cpp
        Tetrimino.cpp
        Tetrimino.hpp)
