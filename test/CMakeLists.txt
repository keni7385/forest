cmake_minimum_required(VERSION 3.0.0)

add_executable(test_all
              src/main.cpp
              src/avltree.cpp
              src/rbtree.cpp
              src/splaytree.cpp)
target_link_libraries(test_all forest)
target_link_libraries(test_all catch)
