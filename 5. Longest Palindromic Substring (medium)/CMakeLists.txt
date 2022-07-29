cmake_minimum_required(VERSION 3.20)
project(5-longest-palindromic-substring)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(5-longest-palindromic-substring
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
