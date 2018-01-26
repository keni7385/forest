#!/bin/bash
curl -O https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch.hpp -o include/catch.hpp
cd tests
make $MAKEFLAGS
