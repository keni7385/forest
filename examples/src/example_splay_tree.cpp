#include <forest/splay_tree.h>
#include <iostream>
#include <string>

auto handler = [](const int & key, const std::string & value) { std::cout << key << "->" << value << std::endl; };

int main(int argc, char const *argv[]) {
  std::cout << "======================" << std::endl;
  std::cout << "[ Splay Tree Example ]" << std::endl;
  std::cout << "======================" << std::endl;

  std::cout << std::endl;

  forest::splay_tree <int, std::string> splay_tree;

  splay_tree.insert(2 , "Thor");
  splay_tree.insert(4 , "Odin");
  splay_tree.insert(90, "Loki");
  splay_tree.insert(3 , "Baldr");
  splay_tree.insert(0 , "Frigg");
  splay_tree.insert(14, "Eir");
  splay_tree.insert(45, "Heimdall");

  std::cout << "Pre Order Traversal" << std::endl;
  splay_tree.pre_order_traversal(handler);
  std::cout << std::endl;

  std::cout << "In Order Traversal" << std::endl;
  splay_tree.in_order_traversal(handler);
  std::cout << std::endl;

  std::cout << "Post Order Traversal" << std::endl;
  splay_tree.post_order_traversal(handler);
  std::cout << std::endl;

  std::cout << "Breadth First Traversal" << std::endl;
  splay_tree.breadth_first_traversal(handler);
  std::cout << std::endl;

  auto min = splay_tree.minimum();
  if (min != nullptr) {
    std::cout << "Minimum: " << min->key << std::endl;
  }

  auto max = splay_tree.maximum();
  if (max != nullptr) {
    std::cout << "Maximum: " << max->key << std::endl;
  }

  auto predecessor = splay_tree.predecessor(90);
  if (predecessor != nullptr) {
    std::cout << "Predecessor of 90: " << predecessor->key << std::endl;
  }

  auto successor = splay_tree.successor(3);
  if (successor != nullptr) {
    std::cout << "Successor of 3: " << successor->key << std::endl;
  }

  std::cout << "Height: " << splay_tree.height() << std::endl;
  std::cout << "Size: " << splay_tree.size() << std::endl;
	std::cout << "Empty: " << (splay_tree.empty() ? "yes" : "no") << std::endl;

  auto n = splay_tree.search(3);
  if (n != nullptr) {
    std::cout << std::endl;
    std::cout << "Found node with key 3" << std::endl;
  }

  std::cout << std::endl;

  return 0;
}