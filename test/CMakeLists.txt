cmake_minimum_required(VERSION 3.0.0)

project("test")

set(TestAVLTreeSource "src/TestAVLTree.cpp")
set(TestBinarySearchTreeSource "src/TestBinarySearchTree.cpp")
set(TestRedBlackTreeSource "src/TestRedBlackTree.cpp")
set(TestSplayTreeSource "src/TestSplayTree.cpp")

if (CMAKE_COMPILER_IS_GNUCC)
  option(ENABLE_COVERAGE OFF)

  if (ENABLE_COVERAGE)
    add_compile_options(--coverage -O0)
  endif()
endif()

enable_testing()

add_executable(TestAVLTree ${TestAVLTreeSource})
target_link_libraries(TestAVLTree Catch2 forest)

add_executable(TestBinarySearchTree ${TestBinarySearchTreeSource})
target_link_libraries(TestBinarySearchTree Catch2 forest)

add_executable(TestRedBlackTree ${TestRedBlackTreeSource})
target_link_libraries(TestRedBlackTree Catch2 forest)

add_executable(TestSplayTree ${TestSplayTreeSource})
target_link_libraries(TestSplayTree Catch2 forest)

if (CMAKE_COMPILER_IS_GNUCC)
  if (ENABLE_COVERAGE)
    target_link_libraries(TestAVLTree --coverage)
	target_link_libraries(TestBinarySearchTree --coverage)
	target_link_libraries(TestRedBlackTree --coverage)
	target_link_libraries(TestSplayTree --coverage)
  endif()
endif()

add_test(AVLTree TestAVLTree)
add_test(BinarySearchTree TestBinarySearchTree)
add_test(RedBlackTree TestRedBlackTree)
add_test(SplayTree TestSplayTree)