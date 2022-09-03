cmake_minimum_required(VERSION 3.20)
project(1379-find-a-corresponding-node-of-a-binary-tree-in-a-clone-of-that-tree)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(1379-find-a-corresponding-node-of-a-binary-tree-in-a-clone-of-that-tree
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
