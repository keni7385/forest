project(tests)

add_executable(tests
              src/main.cpp
              src/avl_tree.cpp
              src/red_black_tree.cpp
              src/splay_tree.cpp)
target_link_libraries(tests forest)
target_link_libraries(tests catch)
