project(forestExamples LANGUAGES CXX)

add_custom_target(examples)

set(forest_examples
        example_avl_tree
        example_binary_search_tree
        example_red_black_tree
        example_splay_tree)

foreach(forest_example IN LISTS forest_examples)

    add_executable(
        ${forest_example}
            ${forest_example}.cpp)

    target_compile_features(
        ${forest_example}
            PRIVATE
              cxx_std_11)

    target_link_libraries(
        ${forest_example}
            PRIVATE
              Forest::forest)

add_dependencies(
    examples
        ${forest_example})

endforeach()
