cmake_minimum_required(VERSION 3.29)
project(postfixCalculator C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(postfixCalculator
        calculator.c
        main.c
        stack.c
        tests.c)
