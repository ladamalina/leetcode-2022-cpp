cmake_minimum_required(VERSION 3.20)
project(rearrange-array-elements-by-sign)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(rearrange-array-elements-by-sign
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
