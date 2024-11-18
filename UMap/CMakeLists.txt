cmake_minimum_required(VERSION 3.29)
project(UMap)
set(CMAKE_CXX_STANDARD 23)

set(MYUMAP_SHARED_LIBS OFF)

include(FetchContent)

add_subdirectory(lib)
add_subdirectory(googleTests)
add_subdirectory(benchmarks)
