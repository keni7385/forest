![forest logo](forest.png)

[![Build status](https://ci.appveyor.com/api/projects/status/8e5jutnq0a8b458f/branch/master?svg=true)](https://ci.appveyor.com/project/xorz57/forest/branch/master)
[![Build Status](https://travis-ci.org/xorz57/forest.svg?branch=master)](https://travis-ci.org/xorz57/forest)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/f2eb2dcf98794d03b5cf0d4c9910db39)](https://www.codacy.com/app/xorz57/forest?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=xorz57/forest&amp;utm_campaign=Badge_Grade)
[![codecov](https://codecov.io/gh/xorz57/forest/branch/master/graph/badge.svg)](https://codecov.io/gh/xorz57/forest)

## Features

|Operations|`avltree.hpp`|`rbtree.hpp`|`splaytree.hpp`|
|---|---|---|---|
|`insert(key, value)`|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|`search(key)`|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|`delete(key)`|:x:|:x:|:x:|
|`pre_order_traversal(handler)`|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|`in_order_traversal(handler)`|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|`post_order_traversal(handler)`|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|`breadth_first_traversal(handler)`|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|`in_order_predecessor(key)`|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|`in_order_succecessor(key)`|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
|`root()`|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|

## Installation

#### Use your favorite package manager
- `vcpkg install forest --head`

#### Or simply [download](https://github.com/xorz57/forest/releases/latest) the header files

#### Or use CMake

```sh
$ mkdir build
$ cmake ..
$ sudo make install
```

#### Or use [Buck](https://buckbuild.com/)

```sh
$ buck run test 
$ buck run examples:avltree
$ buck run examples:rbtree
$ buck run examples:splaytree
```

## Examples

#### Inserting nodes

```cpp
#include "rbtree.h"
#include <string>

int main() {
  forest::rbtree <int, std::string> rbtree;

  rbtree.insert(2 , "Thor");
  rbtree.insert(4 , "Odin");
  rbtree.insert(90, "Loki");
  rbtree.insert(3 , "Baldr");
  rbtree.insert(0 , "Frigg");
  rbtree.insert(14, "Eir");
  rbtree.insert(45, "Heimdall");

  return 0;
}
```

#### Searching nodes

```cpp
#include "rbtree.h"
#include <string>

int main() {
  forest::rbtree <int, std::string> rbtree;

  rbtree.insert(2 , "Thor");
  rbtree.insert(4 , "Odin");
  rbtree.insert(90, "Loki");
  rbtree.insert(3 , "Baldr");
  rbtree.insert(0 , "Frigg");
  rbtree.insert(14, "Eir");
  rbtree.insert(45, "Heimdall");

  auto result = rbtree.search(3);
  if (result != nullptr) {
    std::cout << "Found node with key 3" << std::endl;
  }

  return 0;
}
```

#### Traversing a tree
###### Functions `in_order_traversal()`, `pre_order_traversal()`, `post_order_traversal()` are recursive and should be used with caution
```cpp
#include "rbtree.h"
#include <string>

int main() {
  forest::rbtree <int, std::string> rbtree;

  rbtree.insert(2 , "Thor");
  rbtree.insert(4 , "Odin");
  rbtree.insert(90, "Loki");
  rbtree.insert(3 , "Baldr");
  rbtree.insert(0 , "Frigg");
  rbtree.insert(14, "Eir");
  rbtree.insert(45, "Heimdall");

  rbtree.pre_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  rbtree.in_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  rbtree.post_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  return 0;
}
```

#### Finding the root

```cpp
#include "rbtree.h"
#include <string>

int main() {
  forest::rbtree <int, std::string> rbtree;

  rbtree.insert(2 , "Thor");
  rbtree.insert(4 , "Odin");
  rbtree.insert(90, "Loki");
  rbtree.insert(3 , "Baldr");
  rbtree.insert(0 , "Frigg");
  rbtree.insert(14, "Eir");
  rbtree.insert(45, "Heimdall");

  auto root = rbtree.root();
  if (root != nullptr) {
    std::cout << "Root: " << root->key << std::endl;
  }

  return 0;
}
```

#### Finding the node with the minimum or maximum key

```cpp
#include "rbtree.h"
#include <string>

int main() {
  forest::rbtree <int, std::string> rbtree;

  rbtree.insert(2 , "Thor");
  rbtree.insert(4 , "Odin");
  rbtree.insert(90, "Loki");
  rbtree.insert(3 , "Baldr");
  rbtree.insert(0 , "Frigg");
  rbtree.insert(14, "Eir");
  rbtree.insert(45, "Heimdall");

  auto min = rbtree.minimum();
  if (min != nullptr) {
    std::cout << "Minimum: " << min->key << std::endl;
  }

  auto max = rbtree.maximum();
  if (max != nullptr) {
    std::cout << "Maximum: " << max->key << std::endl;
  }

  return 0;
}
```

#### Finding the predecessor or successor of a node

```cpp
#include "rbtree.h"
#include <string>

int main() {
  forest::rbtree <int, std::string> rbtree;

  rbtree.insert(2 , "Thor");
  rbtree.insert(4 , "Odin");
  rbtree.insert(90, "Loki");
  rbtree.insert(3 , "Baldr");
  rbtree.insert(0 , "Frigg");
  rbtree.insert(14, "Eir");
  rbtree.insert(45, "Heimdall");

  auto predecessor = rbtree.predecessor(90);
  if (predecessor != nullptr) {
    std::cout << "Predecessor of 90: " << predecessor->key << std::endl;
  }

  auto successor = rbtree.successor(3);
  if (successor != nullptr) {
    std::cout << "Successor of 3: " << successor->key << std::endl;
  }

  return 0;
}
```

#### Calculating the height of a tree
###### Function `height()` is recursive and should be used with caution
```cpp
#include "rbtree.h"
#include <string>

int main() {
  forest::rbtree <int, std::string> rbtree;

  rbtree.insert(2 , "Thor");
  rbtree.insert(4 , "Odin");
  rbtree.insert(90, "Loki");
  rbtree.insert(3 , "Baldr");
  rbtree.insert(0 , "Frigg");
  rbtree.insert(14, "Eir");
  rbtree.insert(45, "Heimdall");

  std::cout << "Height: " << rbtree.height() << std::endl;

  return 0;
}
```

#### Calculating the size of a tree
###### Function `size()` is recursive and should be used with caution
```cpp
#include "rbtree.h"
#include <string>

int main() {
  forest::rbtree <int, std::string> rbtree;

  rbtree.insert(2 , "Thor");
  rbtree.insert(4 , "Odin");
  rbtree.insert(90, "Loki");
  rbtree.insert(3 , "Baldr");
  rbtree.insert(0 , "Frigg");
  rbtree.insert(14, "Eir");
  rbtree.insert(45, "Heimdall");

  std::cout << "Size: " << rbtree.size() << std::endl;

  return 0;
}
```
