cmake_minimum_required(VERSION 3.20)
project(minimum-xor-sum-of-two-arrays)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
set(ignore_Python3_EXECUTABLE "${Python3_EXECUTABLE}")
set(ignore_Python_EXECUTABLE "${Python_EXECUTABLE}")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(minimum-xor-sum-of-two-arrays
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
