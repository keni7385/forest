cmake_minimum_required(VERSION 3.10...3.13)

project("benchmark" LANGUAGES CXX)

add_executable(Benchmark_AVLTree "src/Benchmark_AVLTree.cpp")
target_link_libraries(Benchmark_AVLTree benchmark forest)

add_executable(Benchmark_BinarySearchTree "src/Benchmark_BinarySearchTree.cpp")
target_link_libraries(Benchmark_BinarySearchTree benchmark forest)

add_executable(Benchmark_KDTree "src/Benchmark_KDTree.cpp")
target_link_libraries(Benchmark_KDTree benchmark forest)

add_executable(Benchmark_QuadTree "src/Benchmark_QuadTree.cpp")
target_link_libraries(Benchmark_QuadTree benchmark forest)