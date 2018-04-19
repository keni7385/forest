# Trie

In this example we will create a trie.

::: tip
This implementation makes use of C++14 features
:::

## Include the header file

```cpp
// If you installed the library
#include <forest/trie.h>
```

```cpp
// If you downloaded the header
#include "trie.h"
```

## Create a new tree

Here we create a new trie.

```cpp
forest::trie t;
```

## Insert a new word into the trie

Here we specify the `key` that we want to insert.

```cpp
t.insert("thor");
```

::: danger
Only lower-case characters from 'a' to 'z' are supported.
:::

## Find a word in the trie

```cpp
bool result = t.search("thor");
```
