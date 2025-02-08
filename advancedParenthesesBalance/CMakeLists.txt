cmake_minimum_required(VERSION 3.29)
project(advancedParenthesesBalance C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(advancedParenthesesBalance
        main.c
        parenthesesBalance.c
        stack.c
        tests.c)
