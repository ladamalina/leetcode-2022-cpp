cmake_minimum_required(VERSION 3.20)
project(maximum-score-words-formed-by-letters)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(maximum-score-words-formed-by-letters
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
