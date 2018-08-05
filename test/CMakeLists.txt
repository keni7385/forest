cmake_minimum_required(VERSION 3.0.0)

project(FOREST_TEST)

add_executable(FOREST_TEST
              src/main.cpp
              src/avltree.cpp
              src/rbtree.cpp
              src/splaytree.cpp)
target_link_libraries(FOREST_TEST forest)
target_link_libraries(FOREST_TEST catch)
