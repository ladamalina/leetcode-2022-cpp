cmake_minimum_required(VERSION 3.20)
project(1991-find-the-middle-index-in-array)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(1991-find-the-middle-index-in-array
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
