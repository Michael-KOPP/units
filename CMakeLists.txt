cmake_minimum_required(VERSION 3.0.0)
project(units VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(units main.cpp dimension/dimension.hpp dimension/dimension_op.hpp)

target_include_directories(units PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

