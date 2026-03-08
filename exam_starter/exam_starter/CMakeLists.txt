cmake_minimum_required(VERSION 3.10)
project(exam)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(exam-test exam_test.cpp catch.hpp)
add_executable(exam-main exam_main.cpp)

enable_testing()

add_test(exam-test exam-test)