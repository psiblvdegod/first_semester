cmake_minimum_required(VERSION 3.29)
project(AVL_Tree C)

set(CMAKE_C_STANDARD 11)

add_executable(AVL_Tree main.c
        tree.c
        tree.h
        tests.c
        tests.h
        queryProcessing.c)
