cmake_minimum_required(VERSION 3.20)
project(1137-n-th-tribonacci-number)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(1137-n-th-tribonacci-number
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
