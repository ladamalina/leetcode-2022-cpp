cmake_minimum_required(VERSION 3.20)
project(1584-min-cost-to-connect-all-points)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(1584-min-cost-to-connect-all-points
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
