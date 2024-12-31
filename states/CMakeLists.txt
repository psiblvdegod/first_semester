cmake_minimum_required(VERSION 3.29)
project(states C)

set(CMAKE_C_STANDARD 11)

add_executable(states main.c graph.c tests.c list.c fileProcessing.c)
