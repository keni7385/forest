#!/bin/bash
cd tests
curl -o include/catch.hpp -O https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch.hpp
make $MAKEFLAGS
