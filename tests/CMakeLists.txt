project(tests)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_all
              src/test_main.cpp
              src/test_binary_search_tree.cpp
              src/test_avl_tree.cpp
              src/test_red_black_tree.cpp
              src/test_splay_tree.cpp
              src/test_trie.cpp)
target_link_libraries(test_all forest)
target_link_libraries(test_all catch)
