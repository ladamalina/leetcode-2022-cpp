cmake_minimum_required(VERSION 3.20)
project(729-my-calendar-i)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(729-my-calendar-i
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
