cmake_minimum_required(VERSION 3.20)
project(57-insert-interval)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(57-insert-interval
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
