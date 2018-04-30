cmake_minimum_required (VERSION 3.0.0)

project (forest)

set(CMAKE_CXX_STANDARD 14)

add_library(forest INTERFACE)
target_include_directories(forest INTERFACE include)

option(BUILD_TESTS off)
if(BUILD_TESTS)
	add_subdirectory(tests)
endif()

option(BUILD_EXAMPLES on)
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

option(BUILD_BENCHMARKS off)
if(BUILD_BENCHMARKS)
	add_subdirectory(benchmarks)
endif()
