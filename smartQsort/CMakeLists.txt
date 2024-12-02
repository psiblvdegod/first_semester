cmake_minimum_required(VERSION 3.29)
project(smartQsort C)

set(CMAKE_C_STANDARD 11)

add_executable(smartQsort
        main.c
        tests.h
        tests.c
        sorting.h
        sorting.c)
