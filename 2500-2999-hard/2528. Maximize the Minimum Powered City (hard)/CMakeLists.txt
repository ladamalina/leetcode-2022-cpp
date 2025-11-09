cmake_minimum_required(VERSION 3.20)
project(maximize-the-minimum-powered-city)

set(CMAKE_CXX_STANDARD 20)
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

add_executable(maximize-the-minimum-powered-city
        ${TARGET_SRC}
        ${TARGET_H}
        main.cpp)
