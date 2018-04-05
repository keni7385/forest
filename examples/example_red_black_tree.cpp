#include <forest/red_black_tree.h>
#include <iostream>
#include <string>

auto handler = [](int & key, std::string & value) { std::cout << key << "->" << value << std::endl; };

int main(int argc, char const *argv[]) {
  forest::red_black_tree <int, std::string> red_black_tree;

  red_black_tree.insert(2 , "Thor");
  red_black_tree.insert(4 , "Odin");
  red_black_tree.insert(90, "Loki");
  red_black_tree.insert(3 , "Baldr");
  red_black_tree.insert(0 , "Frigg");
  red_black_tree.insert(14, "Eir");
  red_black_tree.insert(45, "Heimdall");

  std::cout << "Pre Order Traversal" << std::endl;
  red_black_tree.pre_order_traversal(handler);
  std::cout << std::endl;

  std::cout << "In Order Traversal" << std::endl;
  red_black_tree.in_order_traversal(handler);
  std::cout << std::endl;

  std::cout << "Post Order Traversal" << std::endl;
  red_black_tree.post_order_traversal(handler);
  std::cout << std::endl;

  std::cout << "Breadth First Traversal" << std::endl;
  red_black_tree.breadth_first_traversal(handler);
  std::cout << std::endl;

  auto min = red_black_tree.minimum();
  if (min != nullptr) {
    std::cout << "Minimum: " << min->key << std::endl;
  }

  auto max = red_black_tree.maximum();
  if (max != nullptr) {
    std::cout << "Maximum: " << max->key << std::endl;
  }

  auto predecessor = red_black_tree.predecessor(90);
  if (predecessor != nullptr) {
    std::cout << "Predecessor of 90: " << predecessor->key << std::endl;
  }

  auto successor = red_black_tree.successor(3);
  if (successor != nullptr) {
    std::cout << "Successor of 3: " << successor->key << std::endl;
  }

  std::cout << "Height: " << red_black_tree.height() << std::endl;
  std::cout << "Size: " << red_black_tree.size() << std::endl;
	std::cout << "Empty: " << (red_black_tree.empty() ? "yes" : "no") << std::endl;

  auto n = red_black_tree.search(3);
  if (n != nullptr) {
    std::cout << std::endl;
    std::cout << "Found node with key 3" << std::endl;
  }

  return 0;
}