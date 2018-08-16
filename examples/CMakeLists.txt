cmake_minimum_required(VERSION 3.0.0)

project(examples)

add_executable(example_avltree src/avltree.cpp)
target_link_libraries(example_avltree forest)

add_executable(example_rbtree src/rbtree.cpp)
target_link_libraries(example_rbtree forest)

add_executable(example_splaytree src/splaytree.cpp)
target_link_libraries(example_splaytree forest)