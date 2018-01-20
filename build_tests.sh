#!/bin/bash
cd tests
curl -O https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch.hpp
make $MAKEFLAGS
