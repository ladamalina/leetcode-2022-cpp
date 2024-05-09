cmake_minimum_required(VERSION 3.20)
project(minimum-length-of-anagram-concatenation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(minimum-length-of-anagram-concatenation
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
