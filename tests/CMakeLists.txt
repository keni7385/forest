# Copyright (C) 2017 Oleksii Vilchanskyi <alexvilchansky@yahoo.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.
#

project(forestTests LANGUAGES CXX)

add_library(Catch INTERFACE)

target_include_directories(
    Catch
        INTERFACE
          "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(
    ${PROJECT_NAME}
        test.cpp
        test_binary_search_tree.cpp
        test_red_black_tree.cpp
        test_splay_tree.cpp
        test_avl_tree.cpp)

target_compile_features(
    ${PROJECT_NAME}
        PRIVATE
          cxx_std_11)

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE
          Catch
          Forest::forest)

add_test(
    NAME forestTest
    COMMAND ${PROJECT_NAME})
