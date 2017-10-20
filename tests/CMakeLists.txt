project(forestTests LANGUAGES CXX)

message(STATUS "Downloading Catch header")
# External curl is used due to CMake not being built with SSL by default
execute_process(
    COMMAND
      curl -o "${CMAKE_CURRENT_BINARY_DIR}/catch.hpp" https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
    OUTPUT_QUIET
    ERROR_QUIET)

file(STRINGS "${CMAKE_CURRENT_BINARY_DIR}/catch.hpp"
      catch_version
    REGEX " \*  Catch v")

message(STATUS "${catch_version}")

# Generate main test file
file(
    WRITE
    "${CMAKE_CURRENT_BINARY_DIR}/test.cpp" [[
      #define CATCH_CONFIG_MAIN
      #include <catch.hpp>
      ]])

add_library(Catch INTERFACE)

target_include_directories(
    Catch
        INTERFACE
          "${CMAKE_CURRENT_SOURCE_DIR}"
          "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(
    test_forest
        "${CMAKE_CURRENT_BINARY_DIR}/test.cpp"
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
