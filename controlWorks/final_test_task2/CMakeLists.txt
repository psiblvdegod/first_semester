cmake_minimum_required(VERSION 3.29)
project(final_test_task2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(final_test_task2
        list.c
        main.c
        test.c)
