cmake_minimum_required(VERSION 3.29)
project(searchTree C)

set(CMAKE_C_STANDARD 23)

add_executable(searchTree main.c
        tree.c
        tests.c
        dictionary.c
        queryProcessing.c)
