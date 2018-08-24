/*
 * @file example_rbtree.cpp
 * @author George Fotopoulos
 */

#include <forest/rbtree.hpp>
#include <iostream>
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

  rbtree.pre_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  rbtree.in_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  rbtree.post_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  auto root = rbtree.root();
  if (root != nullptr) {
    std::cout << "Root: " << root->key << std::endl;
  }

  auto min = rbtree.minimum();
  if (min != nullptr) {
    std::cout << "Minimum: " << min->key << std::endl;
  }

  auto max = rbtree.maximum();
  if (max != nullptr) {
    std::cout << "Maximum: " << max->key << std::endl;
  }

  auto predecessor = rbtree.predecessor(90);
  if (predecessor != nullptr) {
    std::cout << "Predecessor of 90: " << predecessor->key << std::endl;
  }

  auto successor = rbtree.successor(3);
  if (successor != nullptr) {
    std::cout << "Successor of 3: " << successor->key << std::endl;
  }

  std::cout << "Height: " << rbtree.height() << std::endl;

  std::cout << "Size: " << rbtree.size() << std::endl;

  return 0;
}
