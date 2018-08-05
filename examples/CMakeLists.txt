cmake_minimum_required(VERSION 3.0.0)

project(FOREST_EXAMPLES)

add_executable(FOREST_EXAMPLE_AVLTREE src/avltree.cpp)
target_link_libraries(FOREST_EXAMPLE_AVLTREE forest)

add_executable(FOREST_EXAMPLE_RBTREE src/rbtree.cpp)
target_link_libraries(FOREST_EXAMPLE_RBTREE forest)

add_executable(FOREST_EXAMPLE_SPLAYTREE src/splaytree.cpp)
target_link_libraries(FOREST_EXAMPLE_SPLAYTREE forest)
