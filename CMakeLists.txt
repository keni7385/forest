cmake_minimum_required (VERSION 3.0.0)

project (FOREST)

option(FOREST_BUILD_EXAMPLES OFF)
option(FOREST_BUILD_TESTS OFF)

set(CMAKE_CXX_STANDARD 14)

add_library(forest INTERFACE)
target_include_directories(forest INTERFACE include)

add_library(catch INTERFACE)
target_include_directories(catch INTERFACE ext/catch/include)

if (FOREST_BUILD_TESTS)
  add_subdirectory(test)
endif()

if (FOREST_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")
