cd tests

curl -O https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch.hpp

make $MAKEFLAGS
./test
make clean

rm -f catch.hpp

cd ..

cd examples

make $MAKEFLAGS
./example_binary_search_tree
./example_avl_tree
./example_splay_tree
./example_redblack_tree
make clean

rm -f *.dot

cd ..
