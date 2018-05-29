#include <forest/avl_tree.h>
#include <iostream>
#include <string>

auto handler = [](const int & key, const std::string & value) { std::cout << key << "->" << value << std::endl; };

int main(int argc, char const *argv[]) {
  std::cout << "====================" << std::endl;
  std::cout << "[ AVL Tree Example ]" << std::endl;
  std::cout << "====================" << std::endl;

  std::cout << std::endl;

  forest::avl_tree <int, std::string> avl_tree;

  avl_tree.insert(2 , "Thor");
  avl_tree.insert(4 , "Odin");
  avl_tree.insert(90, "Loki");
  avl_tree.insert(3 , "Baldr");
  avl_tree.insert(0 , "Frigg");
  avl_tree.insert(14, "Eir");
  avl_tree.insert(45, "Heimdall");

  std::cout << "Pre Order Traversal" << std::endl;
  avl_tree.pre_order_traversal(handler);
  std::cout << std::endl;

  std::cout << "In Order Traversal" << std::endl;
  avl_tree.in_order_traversal(handler);
  std::cout << std::endl;

  std::cout << "Post Order Traversal" << std::endl;
  avl_tree.post_order_traversal(handler);
  std::cout << std::endl;

  std::cout << "Breadth First Traversal" << std::endl;
  avl_tree.breadth_first_traversal(handler);
  std::cout << std::endl;

  auto min = avl_tree.minimum();
  if (min != nullptr) {
    std::cout << "Minimum: " << min->key << std::endl;
  }

  auto max = avl_tree.maximum();
  if (max != nullptr) {
    std::cout << "Maximum: " << max->key << std::endl;
  }

  auto predecessor = avl_tree.predecessor(90);
  if (predecessor != nullptr) {
    std::cout << "Predecessor of 90: " << predecessor->key << std::endl;
  }

  auto successor = avl_tree.successor(3);
  if (successor != nullptr) {
    std::cout << "Successor of 3: " << successor->key << std::endl;
  }

  std::cout << "Height: " << avl_tree.height() << std::endl;
  std::cout << "Size: " << avl_tree.size() << std::endl;
	std::cout << "Empty: " << (avl_tree.empty() ? "yes" : "no") << std::endl;

  auto n = avl_tree.search(3);
  if (n != nullptr) {
    std::cout << std::endl;
    std::cout << "Found node with key 3" << std::endl;
  }

  std::cout << std::endl;

  return 0;
}