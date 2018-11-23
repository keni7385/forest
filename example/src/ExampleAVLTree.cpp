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

#include <forest/AVLTree.hpp>
#include <iostream>
#include <string>

int main() {
	forest::AVLTree<int, std::string> AVLTree;

	AVLTree.insert(2, "Thor");
	AVLTree.insert(4, "Odin");
	AVLTree.insert(90, "Loki");
	AVLTree.insert(3, "Baldr");
	AVLTree.insert(0, "Frigg");
	AVLTree.insert(14, "Eir");
	AVLTree.insert(45, "Einar");

	std::cout << "pre_order_traversal()" << std::endl;
	AVLTree.pre_order_traversal([](auto key, auto & value) {
		value += ".";
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "in_order_traversal()" << std::endl;
	AVLTree.in_order_traversal([](auto key, auto & value) {
		value += ".";
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "post_order_traversal()" << std::endl;
	AVLTree.post_order_traversal([](auto key, auto & value) {
		value += ".";
		std::cout << key << "->" << value << std::endl;
	});
	std::cout << std::endl;

	std::cout << "remove(3)" << std::endl;
	AVLTree.remove(3);

	std::cout << "search(3)" << " = ";
	auto result = AVLTree.search(3);
	if (result) {
		std::cout << "Found" << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "minimum()" << " = ";
	auto min = AVLTree.minimum();
	if (min) {
		std::cout << min->key << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "maximum()" << " = ";
	auto max = AVLTree.maximum();
	if (max) {
		std::cout << max->key << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "height()" << " = " << AVLTree.height() << std::endl;

	std::cout << "size()" << " = " << AVLTree.size() << std::endl;

	AVLTree.clear();

#ifdef WIN32
	std::cin.get();
#endif

	return 0;
}
