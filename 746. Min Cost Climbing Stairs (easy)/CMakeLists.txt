cmake_minimum_required(VERSION 3.20)
project(746-min-cost-climbing-stairs)

set(CMAKE_CXX_STANDARD 20)
file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(746-min-cost-climbing-stairs
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
