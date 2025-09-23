cmake_minimum_required(VERSION 3.20)
project(find-the-maximum-sum-of-node-values)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(find-the-maximum-sum-of-node-values
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
