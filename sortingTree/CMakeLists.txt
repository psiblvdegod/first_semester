cmake_minimum_required(VERSION 3.29)
project(sortingTree C)

set(CMAKE_C_STANDARD 11)

add_executable(sortingTree main.c tree.h tree.c sorting.c sorting.h test.c test.h)
