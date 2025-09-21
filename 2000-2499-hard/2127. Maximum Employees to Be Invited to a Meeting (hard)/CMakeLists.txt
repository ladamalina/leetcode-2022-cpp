cmake_minimum_required(VERSION 3.20)
project(maximum-employees-to-be-invited-to-a-meeting)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(maximum-employees-to-be-invited-to-a-meeting
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
