cmake_minimum_required(VERSION 3.20)
project(27-remove-element)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(27-remove-element
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
