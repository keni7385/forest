/*
 * @file example_splaytree.cpp
 * @author George Fotopoulos
 */

#include <forest/splaytree.hpp>
#include <iostream>
#include <string>

int main() {
  forest::splaytree <int, std::string> splaytree;

  splaytree.insert(2 , "Thor");
  splaytree.insert(4 , "Odin");
  splaytree.insert(90, "Loki");
  splaytree.insert(3 , "Baldr");
  splaytree.insert(0 , "Frigg");
  splaytree.insert(14, "Eir");
  splaytree.insert(45, "Heimdall");

  auto result = splaytree.search(3);
  if (result != nullptr) {
    std::cout << "Found node with key 3" << std::endl;
  }

  splaytree.pre_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  splaytree.in_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  splaytree.post_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  auto root = splaytree.root();
  if (root != nullptr) {
    std::cout << "Root: " << root->key << std::endl;
  }

  auto min = splaytree.minimum();
  if (min != nullptr) {
    std::cout << "Minimum: " << min->key << std::endl;
  }

  auto max = splaytree.maximum();
  if (max != nullptr) {
    std::cout << "Maximum: " << max->key << std::endl;
  }

  auto predecessor = splaytree.predecessor(90);
  if (predecessor != nullptr) {
    std::cout << "Predecessor of 90: " << predecessor->key << std::endl;
  }

  auto successor = splaytree.successor(3);
  if (successor != nullptr) {
    std::cout << "Successor of 3: " << successor->key << std::endl;
  }

  std::cout << "Height: " << splaytree.height() << std::endl;

  std::cout << "Size: " << splaytree.size() << std::endl;

  return 0;
}
