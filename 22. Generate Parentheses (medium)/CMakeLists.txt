cmake_minimum_required(VERSION 3.20)
project(22-generate-parentheses)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(22-generate-parentheses
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
