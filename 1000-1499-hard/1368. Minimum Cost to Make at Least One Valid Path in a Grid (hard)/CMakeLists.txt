cmake_minimum_required(VERSION 3.20)
project(minimum-cost-to-make-at-least-one-valid-path-in-a-grid)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas -fsanitize=address -fno-omit-frame-pointer")
set(ignore_Python3_EXECUTABLE "${Python3_EXECUTABLE}")
set(ignore_Python_EXECUTABLE "${Python_EXECUTABLE}")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(minimum-cost-to-make-at-least-one-valid-path-in-a-grid
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
