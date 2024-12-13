cmake_minimum_required(VERSION 3.29)
project(modulesAndFiles C)

set(CMAKE_C_STANDARD 11)

add_executable(modulesAndFiles main.c hashTable.c list.c tests.c)
