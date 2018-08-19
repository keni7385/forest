cmake_minimum_required(VERSION 3.0.0)

project(FOREST_TESTS)

if (CMAKE_COMPILER_IS_GNUCC)
  option(ENABLE_COVERAGE OFF)

  if (ENABLE_COVERAGE)
    add_compile_options(--coverage -O0)
  endif()
endif()

enable_testing()

add_executable(test_forest src/main.cpp
                           src/avltree.cpp
                           src/rbtree.cpp
                           src/splaytree.cpp)
target_link_libraries(test_forest Catch2 forest)

if (CMAKE_COMPILER_IS_GNUCC)
  if (ENABLE_COVERAGE)
    target_link_libraries(test_forest --coverage)
  endif()
endif()

add_test(forest test_forest)
