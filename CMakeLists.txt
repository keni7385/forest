cmake_minimum_required(VERSION 3.10...3.13)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.113.tar.gz"
    SHA1 "ad0f405f150bd66c2a2d828e58e977e567c20486"
)

project(forest LANGUAGES CXX VERSION 10.1.5)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_EXAMPLES OFF)
option(BUILD_TESTS OFF)
option(BUILD_BENCHMARKS OFF)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:10000000")
endif()

add_library(forest INTERFACE)
target_include_directories(forest
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/forest>
        $<INSTALL_INTERFACE:include/forest>  # <prefix>/include/forest
)

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

# Installation

set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")
set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")

set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

include(CMakePackageConfigHelpers)

# Use:
#   * PROJECT_VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)


# Use:
#   * 'TARGETS_EXPORT_NAME'
configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

install(
    TARGETS forest
    EXPORT "${TARGETS_EXPORT_NAME}"
    INCLUDES DESTINATION "${include_install_dir}"
)

install(
    DIRECTORY "include/forest"
    DESTINATION "${include_install_dir}"
)

install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

install(
    EXPORT "${TARGETS_EXPORT_NAME}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)

# CPack

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
