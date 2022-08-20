cmake_minimum_required(VERSION 3.20)
project(509-fibonacci-number)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(509-fibonacci-number
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
