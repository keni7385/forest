cmake_minimum_required (VERSION 3.0.0)

project (forest)

add_library(forest INTERFACE)
target_include_directories(forest INTERFACE include)

add_library(catch INTERFACE)
target_include_directories(catch INTERFACE ext/catch)

option(BUILD_TESTS ON)
if(BUILD_TESTS)
	add_subdirectory(tests)
endif()

option(BUILD_EXAMPLES ON)
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
