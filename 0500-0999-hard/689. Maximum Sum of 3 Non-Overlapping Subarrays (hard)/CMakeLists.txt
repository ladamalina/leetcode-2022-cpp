cmake_minimum_required(VERSION 3.20)
project(maximum-sum-of-3-non-overlapping-subarrays)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(maximum-sum-of-3-non-overlapping-subarrays
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
