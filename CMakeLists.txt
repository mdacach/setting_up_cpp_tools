cmake_minimum_required(VERSION 3.22)

# Set up project name
set(PROJECT_NAME soundex)
project(${PROJECT_NAME})

# Set up C++ version to be used, globally
set(CMAKE_CXX_STANDARD 17)

# Set compiler warnings
option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

# I use GCC, on Linux
set(GCC_WARNINGS " \
        -Wall -Wextra -Wshadow -Wnon-virtual-dtor \
        -pedantic -Wold-style-cast -Wcast-align \
        -Woverloaded-virtual -Wpedantic -Wconversion \
        -Wsign-conversion -Wmisleading-indentation \
        -Wduplicated-cond -Wduplicated-branches \
        -Wlogical-op -Wnull-dereference \
        -Wuseless-cast -Wdouble-promotion \
        -Wformat=2 -std=c++17 ")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_WARNINGS}")

if (WARNINGS_AS_ERRORS)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Werror ") # Append to previous warnings
endif ()

# Static Analyzers (Thanks to https://github.com/euripedesrocha/ctdsp/blob/master/cmake/StaticAnalyzers.cmake)
option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" ON)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" ON)

if (ENABLE_CPPCHECK)
    find_program(CPPCHECK cppcheck)
    if (CPPCHECK)
        set(CMAKE_CXX_CPPCHECK ${CPPCHECK} --suppress=missingInclude --enable=all
                --inline-suppr --inconclusive -i ${CMAKE_SOURCE_DIR}/imgui/lib)
    else ()
        message(SEND_ERROR "cppcheck requested but executable not found")
    endif ()
endif ()

if (ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if (CLANGTIDY)
        set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
    else ()
        message(SEND_ERROR "clang-tidy requested but executable not found")
    endif ()
endif ()

# Address and UB sanitizers
option(ENABLE_SANITIZERS "Enable address and undefined behavior sanitizers" ON)
if (ENABLE_SANITIZERS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
endif ()

add_executable(${PROJECT_NAME}
        main.cpp)

add_subdirectory(tests)
