cmake_minimum_required(VERSION 3.10)
project(digital-filter-lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

include_directories(include)

set(SOURCES
    src/main.cpp
    src/fir_filter.cpp
    src/iir_filter.cpp
    src/window.cpp
)

add_executable(test_filters ${SOURCES})
