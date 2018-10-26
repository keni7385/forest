/*
 * @file SplayTree.cpp
 * @author George Fotopoulos
 */

#include <forest/SplayTree.hpp>
#include <iostream>
#include <string>

int main() {
	forest::SplayTree <int, std::string> SplayTree;

	SplayTree.insert(2 , "Thor");
	SplayTree.insert(4 , "Odin");
	SplayTree.insert(90, "Loki");
	SplayTree.insert(3 , "Baldr");
	SplayTree.insert(0 , "Frigg");
	SplayTree.insert(14, "Eir");
	SplayTree.insert(45, "Heimdall");

	std::cout << "pre_order_traversal()" << std::endl;
	SplayTree.pre_order_traversal([](auto key, auto value) {
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "in_order_traversal()" << std::endl;
	SplayTree.in_order_traversal([](auto key, auto value) {
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "post_order_traversal()" << std::endl;
	SplayTree.post_order_traversal([](auto key, auto value) {
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "search(3)" << " = ";
	auto result = SplayTree.search(3);
	if (result != nullptr) {
		std::cout << "Found" << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "minimum()" << " = ";
	auto min = SplayTree.minimum();
	if (min != nullptr) {
		std::cout << min->key << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "maximum()" << " = ";
	auto max = SplayTree.maximum();
	if (max != nullptr) {
		std::cout << max->key << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "height()" << " = " << SplayTree.height() << std::endl;

	std::cout << "size()" << " = " << SplayTree.size() << std::endl;

#ifdef WIN32
	std::cin.get();
#endif

	return 0;
}
