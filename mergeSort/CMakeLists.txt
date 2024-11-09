cmake_minimum_required(VERSION 3.29)
project(mergeSort C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(mergeSort
        list.c
        list.h
        main.c
        mergeSort.c
        mergeSort.h
        contact.h
        contact.c
        tests.c
        tests.h
        contacts.txt)
