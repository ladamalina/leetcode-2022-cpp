cmake_minimum_required(VERSION 3.20)
project(229-majority-element-ii)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(229-majority-element-ii
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
