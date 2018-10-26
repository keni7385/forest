/*
 * @file BinarySearchTree.cpp
 * @author George Fotopoulos
 */

#include <forest/BinarySearchTree.hpp>
#include <iostream>
#include <string>

int main() {
	forest::BinarySearchTree <int, std::string> BinarySearchTree;

	BinarySearchTree.insert(2 , "Thor");
	BinarySearchTree.insert(4 , "Odin");
	BinarySearchTree.insert(90, "Loki");
	BinarySearchTree.insert(3 , "Baldr");
	BinarySearchTree.insert(0 , "Frigg");
	BinarySearchTree.insert(14, "Eir");
	BinarySearchTree.insert(45, "Heimdall");

	std::cout << "pre_order_traversal()" << std::endl;
	BinarySearchTree.pre_order_traversal([](auto key, auto value) {
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "in_order_traversal()" << std::endl;
	BinarySearchTree.in_order_traversal([](auto key, auto value) {
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "post_order_traversal()" << std::endl;
	BinarySearchTree.post_order_traversal([](auto key, auto value) {
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "search(3)" << " = ";
	auto result = BinarySearchTree.search(3);
	if (result != nullptr) {
		std::cout << "Found" << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "minimum()" << " = ";
	auto min = BinarySearchTree.minimum();
	if (min != nullptr) {
		std::cout << min->key << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "maximum()" << " = ";
	auto max = BinarySearchTree.maximum();
	if (max != nullptr) {
		std::cout << max->key << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "height()" << " = " << BinarySearchTree.height() << std::endl;

	std::cout << "size()" << " = " << BinarySearchTree.size() << std::endl;

#ifdef WIN32
	std::cin.get();
#endif

	return 0;
}
