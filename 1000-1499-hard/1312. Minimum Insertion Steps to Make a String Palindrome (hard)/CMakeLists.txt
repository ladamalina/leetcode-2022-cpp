cmake_minimum_required(VERSION 3.20)
project(minimum-insertion-steps-to-make-a-string-palindrome)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(minimum-insertion-steps-to-make-a-string-palindrome
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
