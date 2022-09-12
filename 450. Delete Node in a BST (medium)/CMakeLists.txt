cmake_minimum_required(VERSION 3.20)
project(450-delete-node-in-a-bst)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(450-delete-node-in-a-bst
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
