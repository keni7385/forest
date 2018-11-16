/*
	MIT License

	Copyright(c) 2017 George Fotopoulos

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <forest/BinarySearchTree.hpp>
#include <iostream>
#include <string>

int main() {
	forest::BinarySearchTree<int, std::string> BinarySearchTree;

	BinarySearchTree.insert(2, "Thor");
	BinarySearchTree.insert(4, "Odin");
	BinarySearchTree.insert(90, "Loki");
	BinarySearchTree.insert(3, "Baldr");
	BinarySearchTree.insert(0, "Frigg");
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

	std::cout << "remove(3)" << std::endl;
	BinarySearchTree.remove(3);

	std::cout << "search(3)" << " = ";
	auto result = BinarySearchTree.search(3);
	if (result) {
		std::cout << "Found" << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "minimum()" << " = ";
	auto min = BinarySearchTree.minimum();
	if (min) {
		std::cout << min->key << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "maximum()" << " = ";
	auto max = BinarySearchTree.maximum();
	if (max) {
		std::cout << max->key << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "height()" << " = " << BinarySearchTree.height() << std::endl;

	std::cout << "size()" << " = " << BinarySearchTree.size() << std::endl;

	BinarySearchTree.clear();

#ifdef WIN32
	std::cin.get();
#endif

	return 0;
}
