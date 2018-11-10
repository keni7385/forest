cmake_minimum_required(VERSION 3.0.0)

project("benchmark")

set(BenchmarkAVLTreeSource "src/BenchmarkAVLTree.cpp")
set(BenchmarkBinarySearchTreeSource "src/BenchmarkBinarySearchTree.cpp")
set(BenchmarkRedBlackTreeSource "src/BenchmarkRedBlackTree.cpp")
set(BenchmarkSplayTreeSource "src/BenchmarkSplayTree.cpp")
set(BenchmarkKDTreeSource "src/BenchmarkKDTree.cpp")
set(BenchmarkQuadTreeSource "src/BenchmarkQuadTree.cpp")

add_executable(BenchmarkAVLTree ${BenchmarkAVLTreeSource})
target_link_libraries(BenchmarkAVLTree benchmark forest)

add_executable(BenchmarkBinarySearchTree ${BenchmarkBinarySearchTreeSource})
target_link_libraries(BenchmarkBinarySearchTree benchmark forest)

add_executable(BenchmarkRedBlackTree ${BenchmarkRedBlackTreeSource})
target_link_libraries(BenchmarkRedBlackTree benchmark forest)

add_executable(BenchmarkSplayTree ${BenchmarkSplayTreeSource})
target_link_libraries(BenchmarkSplayTree benchmark forest)

add_executable(BenchmarkKDTree ${BenchmarkKDTreeSource})
target_link_libraries(BenchmarkKDTree benchmark forest)

add_executable(BenchmarkQuadTree ${BenchmarkQuadTreeSource})
target_link_libraries(BenchmarkQuadTree benchmark forest)