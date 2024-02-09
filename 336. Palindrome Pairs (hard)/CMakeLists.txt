cmake_minimum_required(VERSION 3.20)
project(palindrome-pairs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunknown-pragmas -fsanitize=undefined -fno-sanitize-recover")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(palindrome-pairs
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
