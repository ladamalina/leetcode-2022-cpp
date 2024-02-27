cmake_minimum_required(VERSION 3.20)
project(set-intersection-size-at-least-two)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(set-intersection-size-at-least-two
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
