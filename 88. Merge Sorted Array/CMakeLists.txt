cmake_minimum_required(VERSION 3.20)
project(88-merge-sorted-array)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(88-merge-sorted-array
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
