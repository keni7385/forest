cmake_minimum_required(VERSION 3.0.0)

add_executable(avltree src/avltree.cpp)
target_link_libraries(avltree forest)

add_executable(rbtree src/rbtree.cpp)
target_link_libraries(rbtree forest)

add_executable(splaytree src/splaytree.cpp)
target_link_libraries(splaytree forest)
