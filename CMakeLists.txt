cmake_minimum_required(VERSION 3.28)
project(dsa)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.16.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(string_match
    src/string_match/kmp.cpp
    src/string_match/bm.cpp
    src/string_match/kr.cpp
)

add_library(lru
    src/lru/lru_cache.cpp
)
target_include_directories(lru PUBLIC ${CMAKE_SOURCE_DIR}/include)

file(GLOB TEST_SOURCES "${CMAKE_SOURCE_DIR}/test/*_test.cpp")
add_executable(dsa_test ${TEST_SOURCES})
target_include_directories(dsa_test PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(dsa_test PRIVATE ${CMAKE_SOURCE_DIR}/third_party ${googletest_INCLUDE_DIR})
target_link_libraries(dsa_test PUBLIC string_match lru gtest_main)

add_executable(main ${CMAKE_SOURCE_DIR}/main.cpp)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/third_party)
target_link_libraries(main PUBLIC string_match lru)