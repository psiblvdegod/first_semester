cmake_minimum_required(VERSION 3.29)
project(search C)

set(CMAKE_C_STANDARD 11)

add_executable(search
        main.c sorting.h sorting.c tests.c tests.h search.c search.h)
