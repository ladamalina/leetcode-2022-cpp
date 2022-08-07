cmake_minimum_required(VERSION 3.20)
project(104-maximum-depth-of-binary-tree)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(104-maximum-depth-of-binary-tree
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
