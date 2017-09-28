cmake_minimum_required(VERSION 3.9)

project(forest)

set (CMAKE_CXX_STANDARD 11)

install(DIRECTORY forest DESTINATION include FILES_MATCHING PATTERN "*.h")

include_directories(.)

add_executable(bsearch
  examples/example_binary_search_tree.cpp)

add_executable(rbtree
  examples/example_red_black_tree.cpp)

add_executable(stree
  examples/example_splay_tree.cpp)

add_executable(forest_test
  tests/test.cpp
  tests/catch.hpp
  tests/test_binary_search_tree.cpp
  tests/test_red_black_tree.cpp
  tests/test_splay_tree.cpp)
