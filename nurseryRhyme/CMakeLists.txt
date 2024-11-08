cmake_minimum_required(VERSION 3.29)
project(nurseryRhyme C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(nurseryRhyme
        list.c
        list.h
        main.c
        tests.c
        tests.h
        theRevenant.c
        theRevenant.h)
