cmake_minimum_required(VERSION 3.20)
project(62-unique-paths)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(62-unique-paths
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
