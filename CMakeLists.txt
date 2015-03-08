cmake_minimum_required(VERSION 2.8.8)
project(Stats)
set(EXECUTABLE_NAME "stats")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
add_subdirectory(src)

