cmake_minimum_required(VERSION 3.20)
project(429-n-ary-tree-level-order-traversal)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(429-n-ary-tree-level-order-traversal
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
