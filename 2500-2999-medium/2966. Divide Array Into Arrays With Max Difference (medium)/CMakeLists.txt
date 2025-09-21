cmake_minimum_required(VERSION 3.20)
project(divide-array-into-arrays-with-max-difference)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(divide-array-into-arrays-with-max-difference
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
