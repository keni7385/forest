![forest logo](forest.png)

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/7e0feb3d79ca41649aa207eeeef065dc)](https://www.codacy.com/app/xorz57/forest?utm_source=github.com&utm_medium=referral&utm_content=xorz57/forest&utm_campaign=badger)
[![Build Status](https://travis-ci.org/xorz57/forest.svg?branch=master)](https://travis-ci.org/xorz57/forest)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Features

|Operations|Binary Search Tree|AVL Tree|Red-Black Tree|Splay Tree|
|---|---|---|---|---|
|insert(key, value)|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|search(key)|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|delete(key)|:x:|:x:|:x:|:x:|
|pre_order_traversal(handler)|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|in_order_traversal(handler)|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|post_order_traversal(handler)|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|breadth_first_traversal(handler)|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|in_order_predecessor(key)|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|in_order_succecessor(key)|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|root()|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|

## Installation

#### Use your favorite package manager
- `vcpkg install forest --head`

#### Or simply [download](https://github.com/xorz57/forest/releases/latest) the header files

## Examples

#### Inserting nodes

```cpp
#include "red_black_tree.h"
#include <string>

int main() {
  forest::red_black_tree <int, std::string> red_black_tree;

  red_black_tree.insert(2 , "Thor");
  red_black_tree.insert(4 , "Odin");
  red_black_tree.insert(90, "Loki");
  red_black_tree.insert(3 , "Baldr");
  red_black_tree.insert(0 , "Frigg");
  red_black_tree.insert(14, "Eir");
  red_black_tree.insert(45, "Heimdall");

  return 0;
}
```

#### Searching nodes

```cpp
#include "red_black_tree.h"
#include <string>

int main() {
  forest::red_black_tree <int, std::string> red_black_tree;

  red_black_tree.insert(2 , "Thor");
  red_black_tree.insert(4 , "Odin");
  red_black_tree.insert(90, "Loki");
  red_black_tree.insert(3 , "Baldr");
  red_black_tree.insert(0 , "Frigg");
  red_black_tree.insert(14, "Eir");
  red_black_tree.insert(45, "Heimdall");

  auto result = red_black_tree.search(3);
  if (result != nullptr) {
    std::cout << "Found node with key 3" << std::endl;
  }

  return 0;
}
```

#### Traversing a tree
###### Functions `in_order_traversal()`, `pre_order_traversal()`, `post_order_traversal()` are recursive and should be used with caution
```cpp
#include "red_black_tree.h"
#include <string>

int main() {
  forest::red_black_tree <int, std::string> red_black_tree;

  red_black_tree.insert(2 , "Thor");
  red_black_tree.insert(4 , "Odin");
  red_black_tree.insert(90, "Loki");
  red_black_tree.insert(3 , "Baldr");
  red_black_tree.insert(0 , "Frigg");
  red_black_tree.insert(14, "Eir");
  red_black_tree.insert(45, "Heimdall");

  red_black_tree.pre_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  red_black_tree.in_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  red_black_tree.post_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  return 0;
}
```

#### Finding the root

```cpp
#include "red_black_tree.h"
#include <string>

int main() {
  forest::red_black_tree <int, std::string> red_black_tree;

  red_black_tree.insert(2 , "Thor");
  red_black_tree.insert(4 , "Odin");
  red_black_tree.insert(90, "Loki");
  red_black_tree.insert(3 , "Baldr");
  red_black_tree.insert(0 , "Frigg");
  red_black_tree.insert(14, "Eir");
  red_black_tree.insert(45, "Heimdall");

  auto root = red_black_tree.root();
  if (root != nullptr) {
    std::cout << "Root: " << root->key << std::endl;
  }

  return 0;
}
```

#### Finding the node with the minimum or maximum key

```cpp
#include "red_black_tree.h"
#include <string>

int main() {
  forest::red_black_tree <int, std::string> red_black_tree;

  red_black_tree.insert(2 , "Thor");
  red_black_tree.insert(4 , "Odin");
  red_black_tree.insert(90, "Loki");
  red_black_tree.insert(3 , "Baldr");
  red_black_tree.insert(0 , "Frigg");
  red_black_tree.insert(14, "Eir");
  red_black_tree.insert(45, "Heimdall");

  auto min = red_black_tree.minimum();
  if (min != nullptr) {
    std::cout << "Minimum: " << min->key << std::endl;
  }

  auto max = red_black_tree.maximum();
  if (max != nullptr) {
    std::cout << "Maximum: " << max->key << std::endl;
  }

	return 0;
}
```

#### Finding the predecessor or successor of a node

```cpp
#include "red_black_tree.h"
#include <string>

int main() {
  forest::red_black_tree <int, std::string> red_black_tree;

  red_black_tree.insert(2 , "Thor");
  red_black_tree.insert(4 , "Odin");
  red_black_tree.insert(90, "Loki");
  red_black_tree.insert(3 , "Baldr");
  red_black_tree.insert(0 , "Frigg");
  red_black_tree.insert(14, "Eir");
  red_black_tree.insert(45, "Heimdall");

  auto predecessor = red_black_tree.predecessor(90);
  if (predecessor != nullptr) {
    std::cout << "Predecessor of 90: " << predecessor->key << std::endl;
  }

  auto successor = red_black_tree.successor(3);
  if (successor != nullptr) {
    std::cout << "Successor of 3: " << successor->key << std::endl;
  }

  return 0;
}
```

#### Calculating the height of a tree
###### Function `height()` is recursive and should be used with caution
```cpp
#include "red_black_tree.h"
#include <string>

int main() {
  forest::red_black_tree <int, std::string> red_black_tree;

  red_black_tree.insert(2 , "Thor");
  red_black_tree.insert(4 , "Odin");
  red_black_tree.insert(90, "Loki");
  red_black_tree.insert(3 , "Baldr");
  red_black_tree.insert(0 , "Frigg");
  red_black_tree.insert(14, "Eir");
  red_black_tree.insert(45, "Heimdall");

  std::cout << "Height: " << red_black_tree.height() << std::endl;

  return 0;
}
```

#### Calculating the size of a tree
###### Function `size()` is recursive and should be used with caution
```cpp
#include "red_black_tree.h"
#include <string>

int main() {
  forest::red_black_tree <int, std::string> red_black_tree;

  red_black_tree.insert(2 , "Thor");
  red_black_tree.insert(4 , "Odin");
  red_black_tree.insert(90, "Loki");
  red_black_tree.insert(3 , "Baldr");
  red_black_tree.insert(0 , "Frigg");
  red_black_tree.insert(14, "Eir");
  red_black_tree.insert(45, "Heimdall");

  std::cout << "Size: " << red_black_tree.size() << std::endl;

  return 0;
}
```
