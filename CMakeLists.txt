cmake_minimum_required(VERSION 3.9)

project(Forest LANGUAGES CXX VERSION 4.2.1)

# Let CMake find custom modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

include(ForestBuildType)

# Configuration

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE
    STRING "Where to put binaries after compilation.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE
    STRING "Where to put libraries after compilation.")

set(FOREST_BUILD_EXAMPLES      OFF CACHE BOOL "Build usage examples")
set(FOREST_ENABLE_TESTING      OFF CACHE BOOL "Build tests and prepare `test` target")
set(FOREST_BUILD_DOCUMENTATION OFF CACHE BOOL "Build Doxygen documentation")

add_subdirectory(include)

if(FOREST_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(FOREST_ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

if(FOREST_BUILD_DOCUMENTATION)
    add_subdirectory(doc)
endif()
