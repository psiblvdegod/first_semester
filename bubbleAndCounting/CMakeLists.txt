cmake_minimum_required(VERSION 3.29)
project(bubbleAndCounting C)

set(CMAKE_C_STANDARD 11)

add_executable(bubbleAndCounting main.c
tests.h
tests.c
sorting.c
sorting.h)
