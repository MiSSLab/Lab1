cmake_minimum_required(VERSION 3.6)
project(misslab)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES lab1.cpp)
add_executable(misslab ${SOURCE_FILES})
target_link_libraries(misslab gmp gmpxx)
