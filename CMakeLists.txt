cmake_minimum_required (VERSION 3.0.0)

project (forest)

option(BUILD_EXAMPLES OFF)
option(BUILD_TESTS OFF)

set(CMAKE_CXX_STANDARD 14)

add_library(forest INTERFACE)
target_include_directories(forest INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE ${CMAKE_SOURCE_DIR}/ext/Catch2/single_include)

if (BUILD_TESTS)
  add_subdirectory(test)
endif()

if (BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")
