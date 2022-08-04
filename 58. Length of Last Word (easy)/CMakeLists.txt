cmake_minimum_required(VERSION 3.20)
project(58-length-of-last-word)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(58-length-of-last-word
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
