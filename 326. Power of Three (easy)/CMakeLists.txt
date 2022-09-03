cmake_minimum_required(VERSION 3.20)
project(326-power-of-three)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(326-power-of-three
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
