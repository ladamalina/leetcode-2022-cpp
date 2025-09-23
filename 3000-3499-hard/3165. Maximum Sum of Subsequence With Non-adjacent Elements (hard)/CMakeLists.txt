cmake_minimum_required(VERSION 3.20)
project(maximum-sum-of-subsequence-with-non-adjacent-elements)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas -fsanitize=address -fno-omit-frame-pointer") # Clang only
set(ignore_Python3_EXECUTABLE "${Python3_EXECUTABLE}")
set(ignore_Python_EXECUTABLE "${Python_EXECUTABLE}")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(maximum-sum-of-subsequence-with-non-adjacent-elements
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
