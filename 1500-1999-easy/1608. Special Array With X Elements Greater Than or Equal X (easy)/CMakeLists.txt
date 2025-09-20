cmake_minimum_required(VERSION 3.20)
project(special-array-with-x-elements-greater-than-or-equal-x)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas -fsanitize=address -fno-omit-frame-pointer") # Clang only
set(ignore_Python3_EXECUTABLE "${Python3_EXECUTABLE}")
set(ignore_Python_EXECUTABLE "${Python_EXECUTABLE}")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(special-array-with-x-elements-greater-than-or-equal-x
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
