find_package(Doxygen REQUIRED COMPONENTS doxygen)

doxygen_add_docs(
      doc
      "${CMAKE_BINARY_DIR}/include/forest"
    COMMENT
      "Generating Doxygen documentation")
