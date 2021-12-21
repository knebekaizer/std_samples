cmake_minimum_required(VERSION 3.20)
project(std_samples)

set(CMAKE_CXX_STANDARD 14)

add_executable(first first.cpp)
add_executable(fancy_ptr fancy_ptr.cpp fancy_ptr.h)

