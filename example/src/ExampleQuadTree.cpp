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

#include <forest/QuadTree.hpp>
#include <iostream>
#include <array>
#include <vector>

int main() {
	forest::QuadTree <float, 2> QuadTree(0, 0, 10, 10);

	for (float i = -5; i < 5; ++i) {
		std::cout << "insert({ " << i << ", " << i << " })" << std::endl;
		QuadTree.insert({ i, i });
	}

	std::cout << std::endl;

	for (float i = 0; i < 15; ++i) {
		std::cout << "search({ " << i << ", " << i << " })" << " = ";
		if (QuadTree.search({ i, i })) {
			std::cout << "Found" << std::endl;
		}
		else {
			std::cout << "Not Found" << std::endl;
		}
	}

	std::cout << std::endl;

	for (float i = 0; i < 5; ++i) {
		std::cout << "remove({ " << i << ", " << i << " })" << std::endl;
		QuadTree.remove({ i, i });
	}

	std::cout << std::endl;

	auto results = QuadTree.query({ 0, 0, 10, 10 });

	std::cout << "query({ 0, 0, 10, 10 })" << " = {" << std::endl;
	for (auto point : results) {
		std::cout << "(" << point.getX() << ", " << point.getY() << ")" << std::endl;
	}
	std::cout << "}" << std::endl;

	QuadTree.clear();

#ifdef WIN32
	std::cin.get();
#endif

	return 0;
}