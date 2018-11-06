cmake_minimum_required(VERSION 3.0.0)

project("example")

set(ExampleAVLTreeSource "src/ExampleAVLTree.cpp")
set(ExampleBinarySearchTreeSource "src/ExampleBinarySearchTree.cpp")
set(ExampleRedBlackTreeSource "src/ExampleRedBlackTree.cpp")
set(ExampleSplayTreeSource "src/ExampleSplayTree.cpp")
set(ExampleKDTreeSource "src/ExampleKDTree.cpp")
set(ExampleQuadTreeSource "src/ExampleQuadTree.cpp")

add_executable(ExampleAVLTree ${ExampleAVLTreeSource})
target_link_libraries(ExampleAVLTree forest)

add_executable(ExampleBinarySearchTree ${ExampleBinarySearchTreeSource})
target_link_libraries(ExampleBinarySearchTree forest)

add_executable(ExampleRedBlackTree ${ExampleRedBlackTreeSource})
target_link_libraries(ExampleRedBlackTree forest)

add_executable(ExampleSplayTree ${ExampleSplayTreeSource})
target_link_libraries(ExampleSplayTree forest)

add_executable(ExampleKDTree ${ExampleKDTreeSource})
target_link_libraries(ExampleKDTree forest)

add_executable(ExampleQuadTree ${ExampleQuadTreeSource})
target_link_libraries(ExampleQuadTree forest)