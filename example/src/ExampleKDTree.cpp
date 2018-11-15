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

int main() {
	forest::KDTree <float, 4> KDTree;

	forest::KDTree<float, 4>::Points points{
		{ 0, 6, 0, 6 },
		{ 1, 5, 1, 5 },
		{ 2, 4, 2, 4 },
		{ 3, 3, 3, 3 },
		{ 4, 2, 4, 2 },
		{ 5, 1, 5, 1 },
		{ 6, 0, 6, 0 },
	};

	KDTree.fill(points.begin(), points.end());

	std::cout << "search({ 6, 0, 6, 0 })" << " = ";
	if (KDTree.search({ 6, 0, 6, 0 })) {
		std::cout << "Found" << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << std::endl;

	std::cout << "size()" << " = " << KDTree.size() << std::endl;

	std::cout << std::endl;

	std::cout << "remove({ 3, 3, 3, 3 })" << std::endl;
	KDTree.remove({ 3, 3, 3, 3 });

	std::cout << std::endl;

	std::cout << "size()" << " = " << KDTree.size() << std::endl;

	std::cout << std::endl;

	std::cout << "search({ 3, 3, 3, 3 })" << " = ";
	if (KDTree.search({ 3, 3, 3, 3 })) {
		std::cout << "Found" << std::endl;
	}
	else {
		std::cout << "Not Found" << std::endl;
	}

	std::cout << std::endl;

	std::cout << "query({ { 3, 3, 3, 3 }, { 2, 2, 2, 2 } })" << " = {" << std::endl;
	KDTree.query({ { 3, 3, 3, 3 }, { 2, 2, 2, 2 } }, [](auto point) {
		std::cout << "(" << point[0] << ", " << point[1] << ", " << point[2] << ", " << point[3] << ")" << std::endl;
	});
	std::cout << "}" << std::endl;

	std::cout << std::endl;

	std::cout << "clear()" << std::endl;
	KDTree.clear();

	std::cout << std::endl;

	std::cout << "size()" << " = " << KDTree.size() << std::endl;

#ifdef WIN32
	std::cin.get();
#endif

	return 0;
}