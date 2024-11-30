cmake_minimum_required(VERSION 3.29)
project(hashTable C)

set(CMAKE_C_STANDARD 11)

add_executable(hashTable
        main.c
        list.c
        list.h
        hashTable.c
        hashTable.h
        tests.c
        tests.h)
