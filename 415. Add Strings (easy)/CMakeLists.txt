cmake_minimum_required(VERSION 3.20)
project(415-add-strings)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(415-add-strings
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
