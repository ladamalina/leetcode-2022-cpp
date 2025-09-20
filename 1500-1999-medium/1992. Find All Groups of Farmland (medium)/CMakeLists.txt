cmake_minimum_required(VERSION 3.20)
project(find-all-groups-of-farmland)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(find-all-groups-of-farmland
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
