cmake_minimum_required(VERSION 3.10)
project(linalg)
add_library(linalg "source/matrix.cpp")
target_include_directories(linalg PUBLIC include/)