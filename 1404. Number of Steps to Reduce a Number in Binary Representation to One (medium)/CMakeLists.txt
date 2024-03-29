cmake_minimum_required(VERSION 3.20)
project(number-of-steps-to-reduce-a-number-in-binary-representation-to-one)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas -fsanitize=address -fno-omit-frame-pointer") # Clang only
set(ignore_Python3_EXECUTABLE "${Python3_EXECUTABLE}")
set(ignore_Python_EXECUTABLE "${Python_EXECUTABLE}")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(number-of-steps-to-reduce-a-number-in-binary-representation-to-one
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
