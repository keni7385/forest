#include <forest/avltree.hpp>
#include <iostream>
#include <string>

int main() {
  forest::avltree <int, std::string> avltree;

  avltree.insert(2 , "Thor");
  avltree.insert(4 , "Odin");
  avltree.insert(90, "Loki");
  avltree.insert(3 , "Baldr");
  avltree.insert(0 , "Frigg");
  avltree.insert(14, "Eir");
  avltree.insert(45, "Heimdall");

  auto result = avltree.search(3);
  if (result != nullptr) {
    std::cout << "Found node with key 3" << std::endl;
  }

  avltree.pre_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  avltree.in_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  avltree.post_order_traversal([](auto key, auto value) { std::cout << key << "->" << value << std::endl; });

  auto root = avltree.root();
  if (root != nullptr) {
    std::cout << "Root: " << root->key << std::endl;
  }

  auto min = avltree.minimum();
  if (min != nullptr) {
    std::cout << "Minimum: " << min->key << std::endl;
  }

  auto max = avltree.maximum();
  if (max != nullptr) {
    std::cout << "Maximum: " << max->key << std::endl;
  }

  auto predecessor = avltree.predecessor(90);
  if (predecessor != nullptr) {
    std::cout << "Predecessor of 90: " << predecessor->key << std::endl;
  }

  auto successor = avltree.successor(3);
  if (successor != nullptr) {
    std::cout << "Successor of 3: " << successor->key << std::endl;
  }

  std::cout << "Height: " << avltree.height() << std::endl;

  std::cout << "Size: " << avltree.size() << std::endl;

  return 0;
}
