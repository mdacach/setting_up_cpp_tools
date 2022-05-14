cmake_minimum_required(VERSION 3.22)

# Set up project name
project(setting_up_cpp_tools)

# Set up C++ version to be used, globally
set(CMAKE_CXX_STANDARD 17)

# Set compiler warnings
option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" TRUE)

# I use GCC, on Linux
set(GCC_WARNINGS " \
        -Wall -Wextra -Wshadow -Wnon-virtual-dtor \
        -pedantic -Wold-style-cast -Wcast-align \
        -Woverloaded-virtual -Wpedantic -Wconversion \
        -Wsign-conversion -Wmisleading-indentation \
        -Wduplicated-cond -Wduplicated-branches \
        -Wlogical-op -Wnull-dereference \
        -Wuseless-cast -Wdouble-promotion \
        -Wformat=2 ")

if (WARNINGS_AS_ERRORS)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Werror ") # Append to previous warnings
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_WARNINGS}")

add_executable(setting_up_cpp_tools
        main.cpp)
