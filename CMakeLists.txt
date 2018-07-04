cmake_minimum_required (VERSION 3.0.0)

project (forest)

set(CMAKE_CXX_STANDARD 14)

add_library(forest INTERFACE)
target_include_directories(forest INTERFACE include)

add_library(catch INTERFACE)
target_include_directories(catch INTERFACE ext/catch)

add_subdirectory(test)
