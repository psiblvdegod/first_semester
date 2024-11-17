cmake_minimum_required(VERSION 3.29)
project(searchTree C)

set(CMAKE_C_STANDARD 11)

add_executable(searchTree main.c tree.c tree.h tests.c tests.h)
