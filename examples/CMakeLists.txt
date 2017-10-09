# Copyright (C) 2017 Oleksii Vilchanskyi <alexvilchansky@yahoo.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.
#

project(forestExamples LANGUAGES CXX)

add_executable(
    example_binary_search_tree
        example_binary_search_tree.cpp)

target_compile_features(
    example_binary_search_tree
        PRIVATE
          cxx_std_11)

target_link_libraries(
    example_binary_search_tree
        PRIVATE
          Forest::forest)

add_executable(
    example_red_black_tree
        example_red_black_tree.cpp)

target_compile_features(
    example_red_black_tree
        PRIVATE
          cxx_std_11)

target_link_libraries(
    example_red_black_tree
        PRIVATE
          Forest::forest)

add_executable(
    example_splay_tree
        example_splay_tree.cpp)

target_compile_features(
    example_splay_tree
        PRIVATE
          cxx_std_11)

target_link_libraries(
    example_splay_tree
        PRIVATE
          Forest::forest)

add_executable(
    example_avl_tree
        example_avl_tree.cpp)

target_compile_features(
    example_avl_tree
        PRIVATE
          cxx_std_11)

target_link_libraries(
    example_avl_tree
        PRIVATE
          Forest::forest)
