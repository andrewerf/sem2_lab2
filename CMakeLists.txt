cmake_minimum_required(VERSION 3.5)

project(2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O0")

add_executable(2 main.cpp dynamic_array.hpp array_sequence.hpp)
