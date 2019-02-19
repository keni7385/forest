cmake_minimum_required(VERSION 3.10...3.13)

project(forest_test LANGUAGES CXX)

if(CMAKE_COMPILER_IS_GNUCC)
  if(ENABLE_COVERAGE)
    add_compile_options(--coverage -O0)
  endif()
endif()

add_executable(Test_AVLTree "src/Test_AVLTree.cpp")
target_link_libraries(Test_AVLTree Catch2 forest)

add_executable(Test_BinarySearchTree "src/Test_BinarySearchTree.cpp")
target_link_libraries(Test_BinarySearchTree Catch2 forest)

add_executable(Test_KDTree "src/Test_KDTree.cpp")
target_link_libraries(Test_KDTree Catch2 forest)

add_executable(Test_QuadTree "src/Test_QuadTree.cpp")
target_link_libraries(Test_QuadTree Catch2 forest)

if(CMAKE_COMPILER_IS_GNUCC)
  if(ENABLE_COVERAGE)
    target_link_libraries(Test_AVLTree --coverage)
	target_link_libraries(Test_BinarySearchTree --coverage)
	target_link_libraries(Test_KDTree --coverage)
	target_link_libraries(Test_QuadTree --coverage)
  endif()
endif()

add_test(AVLTree Test_AVLTree)
add_test(BinarySearchTree Test_BinarySearchTree)
add_test(KDTree Test_KDTree)
add_test(QuadTree Test_QuadTree)