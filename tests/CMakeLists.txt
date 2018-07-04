cmake_minimum_required(VERSION 3.0.0)

project(tests)

add_executable(tests
              src/main.cpp
              src/avltree.cpp
              src/rbtree.cpp
              src/splaytree.cpp)
target_link_libraries(tests forest)
target_link_libraries(tests catch)
