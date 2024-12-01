cmake_minimum_required(VERSION 3.31)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(aoc)
add_subdirectory("lib")
add_subdirectory("2023/problem1")
# by specifying the include here, the problem1 target is not self-contained
target_include_directories(input PUBLIC "./include/")
target_include_directories(problem1 PUBLIC "./include/")
