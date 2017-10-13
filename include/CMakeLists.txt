# Copyright (C) 2017 Oleksii Vilchanskyi <alexvilchansky@yahoo.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.
#

project(forest LANGUAGES CXX VERSION ${${CMAKE_PROJECT_NAME}_VERSION})

add_library(${PROJECT_NAME} INTERFACE)
add_library(${CMAKE_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

file(
    GLOB headers
    RELATIVE "${CMAKE_CURRENT_LIST_DIR}"
      "*.h")

# Copy headers into build directory in order to be able to write
# #include <forest/smth.h> instead of #include <smth.h> to build examples

foreach(header IN LISTS headers)
    configure_file(
          "${CMAKE_CURRENT_LIST_DIR}/${header}"
          "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${header}"
        COPYONLY)
endforeach()

target_include_directories(
    ${PROJECT_NAME}
        INTERFACE
          $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
          $<INSTALL_INTERFACE:.>) # current directory, relative

target_compile_features(
    ${PROJECT_NAME}
        INTERFACE
          cxx_std_11)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "include")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY ExactVersion)

export(
    EXPORT ${PROJECT_NAME}Targets
    NAMESPACE
      ${CMAKE_PROJECT_NAME}::
    FILE
      "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Targets.cmake")

configure_file(
      "${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake"
      "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake"
    COPYONLY)

install(
    EXPORT ${PROJECT_NAME}Targets
    FILE
      "${PROJECT_NAME}Targets.cmake"
    NAMESPACE
      ${CMAKE_PROJECT_NAME}::
    DESTINATION
      "/usr/lib/cmake/${PROJECT_NAME}")

install(
    FILES
      "${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake"
      "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION
      "/usr/lib/cmake/${PROJECT_NAME}")

install(
    FILES
      ${headers}
    DESTINATION
      include/${PROJECT_NAME})
