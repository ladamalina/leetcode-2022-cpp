cmake_minimum_required(VERSION 3.20)
project(9-palindrome-number)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(9-palindrome-number
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
