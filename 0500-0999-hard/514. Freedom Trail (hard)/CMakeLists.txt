cmake_minimum_required(VERSION 3.20)
project(freedom-trail)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(freedom-trail
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
