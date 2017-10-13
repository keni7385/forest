# Copyright (C) 2017 Oleksii Vilchanskyi <alexvilchansky@yahoo.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.
#

find_package(Doxygen REQUIRED COMPONENTS doxygen)

doxygen_add_docs(
      doc
      "${CMAKE_BINARY_DIR}/include/forest"
    COMMENT
      "Generating Doxygen documentation")
