cmake_minimum_required(VERSION 3.20)
project(7-reverse-integer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(7-reverse-integer
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
