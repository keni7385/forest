/*
 * @file RedBlackTree.cpp
 * @author George Fotopoulos
 */

#include <forest/RedBlackTree.hpp>
#include <iostream>
#include <string>

int main() {
	forest::RedBlackTree <int, std::string> RedBlackTree;

	RedBlackTree.insert(2 , "Thor");
	RedBlackTree.insert(4 , "Odin");
	RedBlackTree.insert(90, "Loki");
	RedBlackTree.insert(3 , "Baldr");
	RedBlackTree.insert(0 , "Frigg");
	RedBlackTree.insert(14, "Eir");
	RedBlackTree.insert(45, "Heimdall");

	std::cout << "pre_order_traversal()" << std::endl;
	RedBlackTree.pre_order_traversal([](auto key, auto value) {
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "in_order_traversal()" << std::endl;
	RedBlackTree.in_order_traversal([](auto key, auto value) {
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "post_order_traversal()" << std::endl;
	RedBlackTree.post_order_traversal([](auto key, auto value) {
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "search(3)" << " = ";
	auto result = RedBlackTree.search(3);
	if (result != nullptr) {
		std::cout << "Found" << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "minimum()" << " = ";
	auto min = RedBlackTree.minimum();
	if (min != nullptr) {
		std::cout << min->key << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "maximum()" << " = ";
	auto max = RedBlackTree.maximum();
	if (max != nullptr) {
		std::cout << max->key << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "height()" << " = " << RedBlackTree.height() << std::endl;

	std::cout << "size()" << " = " << RedBlackTree.size() << std::endl;

#ifdef WIN32
	std::cin.get();
#endif

	return 0;
}
