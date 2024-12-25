cmake_minimum_required(VERSION 3.29)
project(mergeSort C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(mergeSort
        list.c
        main.c
        mergeSort.c
        tests.c
        contactsSorting.c
        contacts.txt)
