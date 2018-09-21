cmake_minimum_required (VERSION 3.0.0)

project (FOREST)

option(BUILD_EXAMPLES OFF)
option(BUILD_TESTS OFF)

set(CMAKE_CXX_STANDARD 14)

add_library(forest INTERFACE)
target_include_directories(forest INTERFACE include)

if (BUILD_TESTS)
  add_library(Catch2 INTERFACE)
  target_include_directories(Catch2 INTERFACE third_party/Catch2/single_include)

  add_subdirectory(test)
endif()

if (BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")
