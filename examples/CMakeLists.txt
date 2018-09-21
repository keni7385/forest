cmake_minimum_required(VERSION 3.0.0)

project(FOREST_EXAMPLES)

add_executable(example_avltree src/example_avltree.cpp)
target_link_libraries(example_avltree forest)

add_executable(example_rbtree src/example_rbtree.cpp)
target_link_libraries(example_rbtree forest)

add_executable(example_splaytree src/example_splaytree.cpp)
target_link_libraries(example_splaytree forest)
