cmake_minimum_required(VERSION 3.29)
project(sortingStation C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(sortingStation
        main.c
        queue.c
        sortingStation.c
        stack.c
        tests.c
        inputValidation.c)
