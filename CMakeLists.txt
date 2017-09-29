cmake_minimum_required(VERSION 3.9)

project(forest)

set (CMAKE_CXX_STANDARD 11)

install(DIRECTORY forest DESTINATION include FILES_MATCHING PATTERN "*.h")

include_directories(.)

add_executable(example_binary_search_tree
  examples/example_binary_search_tree.cpp)

add_executable(example_red_black_tree
  examples/example_red_black_tree.cpp)

add_executable(example_splay_tree
  examples/example_splay_tree.cpp)

add_executable(example_avl_tree
  examples/example_avl_tree.cpp)

add_executable(tests
  tests/test.cpp
  tests/catch.hpp
  tests/test_binary_search_tree.cpp
  tests/test_red_black_tree.cpp
  tests/test_splay_tree.cpp
  tests/test_avl_tree.cpp)
