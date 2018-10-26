![forest logo](forest.png)

[![Build status](https://ci.appveyor.com/api/projects/status/8e5jutnq0a8b458f/branch/master?svg=true)](https://ci.appveyor.com/project/xorz57/forest/branch/master)
[![Build Status](https://travis-ci.org/xorz57/forest.svg?branch=master)](https://travis-ci.org/xorz57/forest)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/f2eb2dcf98794d03b5cf0d4c9910db39)](https://www.codacy.com/app/xorz57/forest?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=xorz57/forest&amp;utm_campaign=Badge_Grade)
[![codecov](https://codecov.io/gh/xorz57/forest/branch/master/graph/badge.svg)](https://codecov.io/gh/xorz57/forest)
[![CodeFactor](https://www.codefactor.io/repository/github/xorz57/forest/badge/master)](https://www.codefactor.io/repository/github/xorz57/forest/overview/master)

## How to Install

#### Using vcpkg (CMake)
- `vcpkg install forest --head`

#### Using buckaroo (Buck)
- `buckaroo install xorz57/forest`

#### Using [CMake](https://cmake.org/)

```sh
$ mkdir build
$ cmake ..
$ sudo make install
```

#### Or simply [download](https://github.com/xorz57/forest/releases/latest) the header files

## How to Build

#### Using [CMake](https://cmake.org/)

```sh
$ mkdir build
$ cmake .. -DBUILD_TESTS=ON -DBUILD_EXAMPLES=ON
$ make
```

#### Using [Buck](https://buckbuild.com/)

```sh
$ buck run test
$ buck run example:AVLTree
$ buck run example:RedBlackTree
$ buck run example:SplayTree
```

## Examples

#### Inserting nodes

```cpp
#include "RedBlackTree.h"
#include <string>

int main() {
  forest::RedBlackTree <int, std::string> RedBlackTree;

  RedBlackTree.insert(2 , "Thor");
  RedBlackTree.insert(4 , "Odin");
  RedBlackTree.insert(90, "Loki");
  RedBlackTree.insert(3 , "Baldr");
  RedBlackTree.insert(0 , "Frigg");
  RedBlackTree.insert(14, "Eir");
  RedBlackTree.insert(45, "Heimdall");

  return 0;
}
```

#### Searching nodes

```cpp
#include "RedBlackTree.h"
#include <string>

int main() {
  forest::RedBlackTree <int, std::string> RedBlackTree;

  RedBlackTree.insert(2 , "Thor");
  RedBlackTree.insert(4 , "Odin");
  RedBlackTree.insert(90, "Loki");
  RedBlackTree.insert(3 , "Baldr");
  RedBlackTree.insert(0 , "Frigg");
  RedBlackTree.insert(14, "Eir");
  RedBlackTree.insert(45, "Heimdall");

  auto result = RedBlackTree.search(3);
  if (result != nullptr) {
    // Do something with result->key or result->value
  }

  return 0;
}
```

#### Traversing a tree
###### Functions `in_order_traversal()`, `pre_order_traversal()`, `post_order_traversal()` are recursive and should be used with caution
```cpp
#include "RedBlackTree.h"
#include <string>

int main() {
  forest::RedBlackTree <int, std::string> RedBlackTree;

  RedBlackTree.insert(2 , "Thor");
  RedBlackTree.insert(4 , "Odin");
  RedBlackTree.insert(90, "Loki");
  RedBlackTree.insert(3 , "Baldr");
  RedBlackTree.insert(0 , "Frigg");
  RedBlackTree.insert(14, "Eir");
  RedBlackTree.insert(45, "Heimdall");

  RedBlackTree.pre_order_traversal([](auto key, auto value) {
    // Do something with key or value
  });

  RedBlackTree.in_order_traversal([](auto key, auto value) {
    // Do something with key or value
  });

  RedBlackTree.post_order_traversal([](auto key, auto value) {
    // Do something with key or value
  });

  return 0;
}
```

#### Finding the node with the minimum or maximum key

```cpp
#include "RedBlackTree.h"
#include <string>

int main() {
  forest::RedBlackTree <int, std::string> RedBlackTree;

  RedBlackTree.insert(2 , "Thor");
  RedBlackTree.insert(4 , "Odin");
  RedBlackTree.insert(90, "Loki");
  RedBlackTree.insert(3 , "Baldr");
  RedBlackTree.insert(0 , "Frigg");
  RedBlackTree.insert(14, "Eir");
  RedBlackTree.insert(45, "Heimdall");

  auto min = RedBlackTree.minimum();
  if (min != nullptr) {
    // Do something with min->key or min->value
  }

  auto max = RedBlackTree.maximum();
  if (max != nullptr) {
    // Do something with max->key or max->value
  }

  return 0;
}
```

#### Calculating the height of a tree

```cpp
#include "RedBlackTree.h"
#include <string>

int main() {
  forest::RedBlackTree <int, std::string> RedBlackTree;

  RedBlackTree.insert(2 , "Thor");
  RedBlackTree.insert(4 , "Odin");
  RedBlackTree.insert(90, "Loki");
  RedBlackTree.insert(3 , "Baldr");
  RedBlackTree.insert(0 , "Frigg");
  RedBlackTree.insert(14, "Eir");
  RedBlackTree.insert(45, "Heimdall");

  std::cout << "Height: " << RedBlackTree.height() << std::endl;

  return 0;
}
```

#### Calculating the size of a tree
###### Function `size()` is recursive and should be used with caution
```cpp
#include "RedBlackTree.h"
#include <string>

int main() {
  forest::RedBlackTree <int, std::string> RedBlackTree;

  RedBlackTree.insert(2 , "Thor");
  RedBlackTree.insert(4 , "Odin");
  RedBlackTree.insert(90, "Loki");
  RedBlackTree.insert(3 , "Baldr");
  RedBlackTree.insert(0 , "Frigg");
  RedBlackTree.insert(14, "Eir");
  RedBlackTree.insert(45, "Heimdall");

  std::cout << "Size: " << RedBlackTree.size() << std::endl;

  return 0;
}
```