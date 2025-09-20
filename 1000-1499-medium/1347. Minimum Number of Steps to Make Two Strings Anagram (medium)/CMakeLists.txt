cmake_minimum_required(VERSION 3.20)
project(minimum-number-of-steps-to-make-two-strings-anagram)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(minimum-number-of-steps-to-make-two-strings-anagram
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
