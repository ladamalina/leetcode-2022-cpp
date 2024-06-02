cmake_minimum_required(VERSION 3.20)
project(gcd-sort-of-an-array)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
set(ignore_Python3_EXECUTABLE "${Python3_EXECUTABLE}")
set(ignore_Python_EXECUTABLE "${Python_EXECUTABLE}")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(gcd-sort-of-an-array
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
