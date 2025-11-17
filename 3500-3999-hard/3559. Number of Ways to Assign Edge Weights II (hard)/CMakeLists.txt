cmake_minimum_required(VERSION 3.20)
project(number-of-ways-to-assign-edge-weights-ii)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Clang Xcode / GCC Docker
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror -Wunknown-pragmas -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -gdwarf-5")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -Wall -Wextra -Werror -Wunknown-pragmas -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -gdwarf-5")

# GCC Brew
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror -Wunknown-pragmas -gdwarf-5")
#set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -Wall -Wextra -Werror -Wunknown-pragmas -gdwarf-5")

set(ignore_Python3_EXECUTABLE "${Python3_EXECUTABLE}")
set(ignore_Python_EXECUTABLE "${Python_EXECUTABLE}")

file(GLOB TARGET_H ./*.h)
file(GLOB TARGET_SRC ./*.cpp)

add_executable(number-of-ways-to-assign-edge-weights-ii
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
