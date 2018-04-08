![forest logo](forest.png)

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/7e0feb3d79ca41649aa207eeeef065dc)](https://www.codacy.com/app/xorz57/forest?utm_source=github.com&utm_medium=referral&utm_content=xorz57/forest&utm_campaign=badger)
[![Build Status](https://travis-ci.org/xorz57/forest.svg?branch=master)](https://travis-ci.org/xorz57/forest)
[![codecov](https://codecov.io/gh/xorz57/forest/branch/master/graph/badge.svg)](https://codecov.io/gh/xorz57/forest)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![CLA assistant](https://cla-assistant.io/readme/badge/xorz57/forest)](https://cla-assistant.io/xorz57/forest)

Forest is an open-source, template library of tree data structures written in C++14.

## Features

|Operations|Binary Search Tree|AVL Tree|Red Black Tree|Splay Tree|Trie|
|---|---|---|---|---|---|
|Insert|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|Search|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|Delete|:x:|:x:|:x:|:x:|:x:|
|Pre Order Traversal|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:||
|In Order Traversal|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:||
|Post Order Traversal|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:||
|Breadth First Traversal|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:||
|In Order Predecessor|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:||
|In Order Successor|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:||

## Installation

#### Use your favorite package manager
- `vcpkg install forest`

#### Or simply download the header files
- [Binary Search Tree](https://github.com/xorz57/forest/releases/download/7.0.5/binary_search_tree.h)
- [AVL Tree](https://github.com/xorz57/forest/releases/download/7.0.5/avl_tree.h)
- [Red Black Tree](https://github.com/xorz57/forest/releases/download/7.0.5/red_black_tree.h)
- [Splay Tree](https://github.com/xorz57/forest/releases/download/7.0.5/splay_tree.h)
- [Trie](https://github.com/xorz57/forest/releases/download/7.0.5/trie.h)

## Example Code

Forest is best explained through [examples](https://github.com/xorz57/forest/tree/master/examples).

```cpp
#include "red_black_tree.h"
#include <string>

auto handler = [](const int & key, const std::string & value) { std::cout << key << "->" << value << std::endl; };

int main() {
	// Generate a red-black tree with integer keys and std::string values
	forest::red_black_tree <int, std::string> red_black_tree;

	// Insert 7 plain nodes
	red_black_tree.insert(2 , "Thor");
	red_black_tree.insert(4 , "Odin");
	red_black_tree.insert(90, "Loki");
	red_black_tree.insert(3 , "Baldr");
	red_black_tree.insert(0 , "Frigg");
	red_black_tree.insert(14, "Eir");
	red_black_tree.insert(45, "Heimdall");

	// Perform In-Order-Traversal
	red_black_tree.in_order_traversal(handler);

	return 0;
}
```