# Red-Black Tree

In this example we will create a red-black tree of `int` keys and `std::string` values.

::: tip
This implementation makes use of C++11 features
:::

## Include the header file

```cpp
// If you installed the library
#include <forest/red_black_tree.h>
```

```cpp
// If you downloaded the header
#include "red_black_tree.h"
```

## Create a new tree

Here we create a new red-black tree.

```cpp
forest::red_black_tree <int, std::string> tree;
```

## Insert a new node into the tree

Here we specify the `key` and the `value` of the new node that we want to insert.

```cpp
tree.insert(2 , "Thor");
```

## Perform pre-order traversal

Here our `lambda function` prints out the key followed by the value of the visited nodes.

```cpp
tree.pre_order_traversal([](auto & key, auto & value) {
  std::cout << key << "->" << value << std::endl;
});
```

::: danger
Performing pre-order traversal uses recursion.
:::

## Perform in-order traversal

Here our `lambda function` prints out the key followed by the value of the visited nodes.

```cpp
tree.in_order_traversal([](auto & key, auto & value) {
  std::cout << key << "->" << value << std::endl;
});
```

::: danger
Performing in-order traversal uses recursion.
:::

## Perform post-order traversal

Here our `lambda function` prints out the key followed by the value of the visited nodes.

```cpp
tree.post_order_traversal([](auto & key, auto & value) {
  std::cout << key << "->" << value << std::endl;
});
```

::: danger
Performing post-order traversal uses recursion.
:::

## Perform breadth-first traversal

Here our `lambda function` prints out the key followed by the value of the visited nodes.

```cpp
tree.breadth_first_traversal([](auto & key, auto & value) {
  std::cout << key << "->" << value << std::endl;
});
```

## Find the node with the minimum key

```cpp
auto min = tree.minimum();
if (min != nullptr) {
  // Process min->key
}
```

::: warning
Always check if the node is `nullptr`.
:::

## Find the node with the maximum key

```cpp
auto max = tree.maximum();
if (max != nullptr) {
  // Process max->key
}
```

::: warning
Always check if the node is `nullptr`.
:::

## Find the in-order predecessor

```cpp
auto predecessor = tree.predecessor(90);
if (predecessor != nullptr) {
  // Process predecessor->key
}
```

::: warning
Always check if the node is `nullptr`.
:::

## Find the in-order successor

```cpp
auto successor = tree.successor(90);
if (successor != nullptr) {
  // Process successor->key
}
```

::: warning
Always check if the node is `nullptr`.
:::

## Find the height of the tree

```cpp
size_t h = tree.height()
```

::: danger
Finding the height of the tree uses recursion.
:::

## Find the number of nodes

```cpp
size_t s = tree.size();
```

::: danger
Finding the number of nodes uses recursion.
:::

## Check if the tree is empty

```cpp
bool e = tree.empty();
```

## Find the node with the given key

```cpp
auto n = tree.search(3);
if (n != nullptr) {
  // Process n->value
}
```

::: warning
Always check if the node is `nullptr`.
:::
