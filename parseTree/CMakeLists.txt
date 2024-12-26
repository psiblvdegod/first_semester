cmake_minimum_required(VERSION 3.29)
project(parseTree C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(parseTree
        main.c
        parse.c
        stack.c
        tests.c
        tree.c)
