cmake_minimum_required(VERSION 3.20)
project(64-minimum-path-sum)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(64-minimum-path-sum
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
