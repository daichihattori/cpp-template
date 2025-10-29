cmake_minimum_required(VERSION 3.19)

project(cpp_template LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(gmp)
include(googletest)

add_library(fp STATIC src/fp.cpp)
target_include_directories(fp PUBLIC include)
target_link_libraries(fp PUBLIC gmp::gmp)

enable_testing()
add_executable(fp_tests test/test_fp.cpp)
target_link_libraries(fp_tests PRIVATE fp GTest::gtest_main)
add_test(NAME fp COMMAND fp_tests)
