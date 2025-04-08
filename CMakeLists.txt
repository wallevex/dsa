cmake_minimum_required(VERSION 3.28)
project(dsa)

set(CMAKE_CXX_STANDARD 17)

add_library(string_match
    src/string_match/kmp.cpp
    src/string_match/bm.cpp
    src/string_match/kr.cpp
)

add_executable(dsa main.cpp)

target_include_directories(dsa PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(dsa PRIVATE string_match)