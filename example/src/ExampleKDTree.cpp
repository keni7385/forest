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

#include <forest/KDTree.hpp>
#include <iostream>
#include <array>

int main() {
	forest::KDTree <float, 2> KDTree;

	KDTree.insert({ 0, 0 });
	KDTree.insert({ -5, 5 });
	KDTree.insert({ 5, 5 });
	KDTree.insert({ -5, -5 });
	KDTree.insert({ 5, -5 });

	std::cout << "size()" << " = " << KDTree.size() << std::endl;

	std::cout << "search({ 5, 5 })" << " = ";
	if (KDTree.search({ 5, 5 })) {
		std::cout << "Found" << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "search({ 1, 1 })" << " = ";
	if (KDTree.search({ 1, 1 })) {
		std::cout << "Found" << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "minimum(0)" << " = ";
	auto min = KDTree.minimum(0);
	if (min) {
		std::cout << "(" << min->point[0] << ", " << min->point[1] << ")" << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << "maximum(0)" << " = ";
	auto max = KDTree.maximum(0);
	if (max) {
		std::cout << "(" << max->point[0] << ", " << max->point[1] << ")" << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	KDTree.remove({ 0, 0 });
	KDTree.remove({ -5, 5 });
	KDTree.remove({ 5, 5 });
	KDTree.remove({ -5, -5 });
	KDTree.remove({ 5, -5 });

	KDTree.clear();

#ifdef WIN32
	std::cin.get();
#endif

	return 0;
}