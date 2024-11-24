cmake_minimum_required(VERSION 3.29)
project(commonestElement C)

set(CMAKE_C_STANDARD 11)

add_executable(commonestElement main.c commonestElement.c commonestElement.h test.c test.h)
