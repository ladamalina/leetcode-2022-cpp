cmake_minimum_required(VERSION 3.20)
project(973-k-closest-points-to-origin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(973-k-closest-points-to-origin
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
