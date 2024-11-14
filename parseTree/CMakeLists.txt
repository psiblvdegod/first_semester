cmake_minimum_required(VERSION 3.29)
project(parseTree C)

set(CMAKE_C_STANDARD 11)

add_executable(parseTree main.c
        tree.c
        tree.h
        parse.h
        parse.c
        stack.c
        stack.h)
