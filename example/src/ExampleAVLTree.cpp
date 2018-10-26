/*
 * @file AVLTree.cpp
 * @author George Fotopoulos
 */

#include <forest/AVLTree.hpp>
#include <iostream>
#include <string>

int main() {
	forest::AVLTree <int, std::string> AVLTree;

	AVLTree.insert(2 , "Thor");
	AVLTree.insert(4 , "Odin");
	AVLTree.insert(90, "Loki");
	AVLTree.insert(3 , "Baldr");
	AVLTree.insert(0 , "Frigg");
	AVLTree.insert(14, "Eir");
	AVLTree.insert(45, "Heimdall");

	std::cout << "pre_order_traversal()" << std::endl;
	AVLTree.pre_order_traversal([](auto key, auto value) {
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "in_order_traversal()" << std::endl;
	AVLTree.in_order_traversal([](auto key, auto value) {
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "post_order_traversal()" << std::endl;
	AVLTree.post_order_traversal([](auto key, auto value) {
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "search(3)" << " = ";
	auto result = AVLTree.search(3);
	if (result != nullptr) {
		std::cout << "Found" << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "minimum()" << " = ";
	auto min = AVLTree.minimum();
	if (min != nullptr) {
		std::cout << min->key << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "maximum()" << " = ";
	auto max = AVLTree.maximum();
	if (max != nullptr) {
		std::cout << max->key << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "height()" << " = " << AVLTree.height() << std::endl;

	std::cout << "size()" << " = " << AVLTree.size() << std::endl;

#ifdef WIN32
	std::cin.get();
#endif

	return 0;
}
