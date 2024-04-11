cmake_minimum_required(VERSION 3.20)
project(path-with-maximum-gold)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(path-with-maximum-gold
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
