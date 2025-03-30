cmake_minimum_required(VERSION 3.29)
project(test1_task1 C)

set(CMAKE_C_STANDARD 11)

add_executable(test1_task1 main.c queue.c test.c maxDigitSum.c errorCode.h)
