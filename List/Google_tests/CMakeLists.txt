cmake_minimum_required(VERSION 3.14)
project(Google_tests VERSION 1.0)


include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Google_Tests_run ListTest.cpp)

target_link_libraries(Google_Tests_run PRIVATE gtest gtest_main List)

include(GoogleTest)
gtest_discover_tests(Google_Tests_run)