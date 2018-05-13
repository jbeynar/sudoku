cmake_minimum_required(VERSION 3.9)
project(sudoku C)

set(CMAKE_C_STANDARD 99)

add_executable(sudoku main.c sudokulib.c sudokulib.h)