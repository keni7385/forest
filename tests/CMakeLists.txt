project(forestTests LANGUAGES CXX)

add_library(Catch INTERFACE)

target_include_directories(
    Catch
        INTERFACE
          "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(
    test_forest
        test.cpp
        test_binary_search_tree.cpp
        test_red_black_tree.cpp
        test_splay_tree.cpp
        test_avl_tree.cpp)

target_compile_features(
    test_forest
        PRIVATE
          cxx_std_11)

target_link_libraries(
    test_forest
        PRIVATE
          Catch
          Forest::forest)

add_test(
    NAME
      ${PROJECT_NAME}
    COMMAND
      test_forest)

# By default, CMake's `test` doesn't behave in an intelligent way
# so a custom target will ensure that:
#
# 1. Test-related targets will be [re]built before building `test` target
# 2. Only required targets will be [re]built (and not all)

add_custom_target(
    check
      COMMAND
        test_forest
      DEPENDS
        test_forest
    USES_TERMINAL)
