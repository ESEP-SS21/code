cmake_minimum_required(VERSION 3.17)
project(ESEP CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories("src")
include_directories("lib")
include_directories("lib/spdlog/include")

add_subdirectory(lib/spdlog)
add_subdirectory(test)


