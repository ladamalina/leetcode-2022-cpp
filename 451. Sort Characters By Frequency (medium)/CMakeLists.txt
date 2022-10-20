cmake_minimum_required(VERSION 3.20)
project(451-sort-characters-by-frequency)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(451-sort-characters-by-frequency
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
