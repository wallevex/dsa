cmake_minimum_required(VERSION 3.28)
project(dsa)

set(CMAKE_CXX_STANDARD 14)

add_executable(dsa main.cpp
        string_match/kmp.cpp)
