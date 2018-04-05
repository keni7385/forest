#include <forest/binary_search_tree.h>
#include <iostream>
#include <string>

auto handler = [](int & key, std::string & value) { std::cout << key << "->" << value << std::endl; };

int main(int argc, char const *argv[]) {
	std::cout << "Binary Search Tree Example" << std::endl;

	forest::binary_search_tree <int, std::string> binary_search_tree;

	binary_search_tree.insert(2 , "Thor");
	binary_search_tree.insert(4 , "Odin");
	binary_search_tree.insert(90, "Loki");
	binary_search_tree.insert(3 , "Baldr");
	binary_search_tree.insert(0 , "Frigg");
	binary_search_tree.insert(14, "Eir");
	binary_search_tree.insert(45, "Heimdall");

	std::cout << "Pre Order Traversal" << std::endl;
	binary_search_tree.pre_order_traversal(handler);
	std::cout << std::endl;

	std::cout << "In Order Traversal" << std::endl;
	binary_search_tree.in_order_traversal(handler);
	std::cout << std::endl;

	std::cout << "Post Order Traversal" << std::endl;
	binary_search_tree.post_order_traversal(handler);
	std::cout << std::endl;

	std::cout << "Breadth First Traversal" << std::endl;
	binary_search_tree.breadth_first_traversal(handler);
	std::cout << std::endl;

	auto min = binary_search_tree.minimum();
	if (min != nullptr) {
		std::cout << "Minimum: " << min->key << std::endl;
	}

	auto max = binary_search_tree.maximum();
	if (max != nullptr) {
		std::cout << "Maximum: " << max->key << std::endl;
	}

	auto predecessor = binary_search_tree.predecessor(90);
	if (predecessor != nullptr) {
		std::cout << "Predecessor of 90: " << predecessor->key << std::endl;
	}

	auto successor = binary_search_tree.successor(3);
	if (successor != nullptr) {
		std::cout << "Successor of 3: " << successor->key << std::endl;
	}

	std::cout << "Height: " << binary_search_tree.height() << std::endl;
	std::cout << "Size: " << binary_search_tree.size() << std::endl;
	std::cout << "Empty: " << (binary_search_tree.empty() ? "yes" : "no") << std::endl;

	auto n = binary_search_tree.search(3);
	if (n != nullptr) {
		std::cout << std::endl;
		std::cout << "Found node with key 3" << std::endl;
	}

	std::cout << std::endl;

	return 0;
}