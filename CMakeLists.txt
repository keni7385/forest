﻿cmake_minimum_required(VERSION 3.10...3.13)

project(forest LANGUAGES CXX VERSION 10.1.5)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_EXAMPLES OFF)
option(BUILD_TESTS OFF)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:10000000")
endif()

add_library(forest INTERFACE)
target_include_directories(forest INTERFACE ${CMAKE_SOURCE_DIR}/include)

if(BUILD_TESTS)
  add_library(Catch2 INTERFACE)
  target_include_directories(Catch2 INTERFACE ${CMAKE_SOURCE_DIR}/vendor/catchorg/Catch2/single_include)

  enable_testing()

  add_subdirectory(test)
endif()

if(BUILD_EXAMPLES)
  add_subdirectory(example)
endif()

if(BUILD_BENCHMARKS)
  set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing Google Benchmark's Tests" FORCE)

  add_subdirectory(vendor/google/benchmark)

  add_subdirectory(benchmark)
endif()

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")

set(CPACK_PACKAGE_NAME "forest")
set(CPACK_PACKAGE_VENDOR "George Fotopoulos")
set(CPACK_PACKAGE_CONTACT "xorz57@protonmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Template Library of Tree Data Structures")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_RPM_PACKAGE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")

include(CPack)