cmake_minimum_required(VERSION 3.29)
project(phoneDirectory C)

set(CMAKE_C_STANDARD 11)

add_executable(phoneDirectory
        main.c tests.c phoneDirectory.c queryProcessing.c)
