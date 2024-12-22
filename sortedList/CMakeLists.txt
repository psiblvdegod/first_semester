cmake_minimum_required(VERSION 3.17)
project(sortedList C)

set(CMAKE_C_STANDARD 11)

add_executable(sortedList main.c list.c tests.c queryProcessing.c)