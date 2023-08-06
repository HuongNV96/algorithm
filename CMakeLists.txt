cmake_minimum_required(VERSION 2.8.11)
project(algorithm)

add_executable(algorithm main2D.cpp Matrix2D.cpp Algorithm2D.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})