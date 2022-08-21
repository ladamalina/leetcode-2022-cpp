cmake_minimum_required(VERSION 3.20)
project(107-binary-tree-level-order-traversal-ii)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(107-binary-tree-level-order-traversal-ii
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
