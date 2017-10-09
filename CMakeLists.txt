# Copyright (C) 2017 xorz57 <fot@ceid.upatras.gr>
# Copyright (C) 2017 Josh Lospinoso <josh@lospi.net>
# Copyright (C) 2017 Tres DuBiel <tres@localhost.localdomain>
# Copyright (C) 2017 Oleksii Vilchanskyi <alexvilchansky@yahoo.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.
#

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

set(BUILD_EXAMPLES OFF CACHE BOOL "Build usage examples")
set(ENABLE_TESTING OFF CACHE BOOL "Build tests and prepare `test` target")

add_subdirectory(include)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
