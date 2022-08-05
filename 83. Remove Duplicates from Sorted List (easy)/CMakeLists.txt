cmake_minimum_required(VERSION 3.20)
project(83-remove-duplicates-from-sorted-list)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(83-remove-duplicates-from-sorted-list
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
