cmake_minimum_required(VERSION 3.3)
project(deuqe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -O2 -O3 -O4 -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(deuqe ${SOURCE_FILES})
