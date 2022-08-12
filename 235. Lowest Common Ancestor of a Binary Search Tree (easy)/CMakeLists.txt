cmake_minimum_required(VERSION 3.20)
project(235-lowest-common-ancestor-of-a-binary-search-tree)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(235-lowest-common-ancestor-of-a-binary-search-tree
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
