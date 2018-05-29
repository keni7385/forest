project(examples)

set(CMAKE_CXX_STANDARD 14)

add_executable(example_binary_search_tree src/example_binary_search_tree.cpp)
target_link_libraries(example_binary_search_tree forest)

add_executable(example_avl_tree src/example_avl_tree.cpp)
target_link_libraries(example_avl_tree forest)

add_executable(example_red_black_tree src/example_red_black_tree.cpp)
target_link_libraries(example_red_black_tree forest)

add_executable(example_splay_tree src/example_splay_tree.cpp)
target_link_libraries(example_splay_tree forest)

add_executable(example_trie src/example_trie.cpp)
target_link_libraries(example_trie forest)
