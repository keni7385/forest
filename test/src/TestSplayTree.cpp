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

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/SplayTree.hpp>

SCENARIO("Test Splay Tree") {
	GIVEN("A Splay Tree") {
		forest::SplayTree <int, int> SplayTree;
		WHEN("The Splay Tree is empty") {
			THEN("Test size") {
				REQUIRE(SplayTree.size() == 0);
			}
			THEN("Test height") {
				REQUIRE(SplayTree.height() == 0);
			}
			THEN("Test maximum") {
				auto max = SplayTree.maximum();
				REQUIRE(max == nullptr);
			}
			THEN("Test minimum") {
				auto min = SplayTree.minimum();
				REQUIRE(min == nullptr);
			}
			THEN("Test search for a node that does not exist") {
				auto result = SplayTree.search(555);
				REQUIRE(result == nullptr);
			}
		}
		WHEN("Nodes are inserted in random order") {
			SplayTree.insert(4 , 0);
			SplayTree.insert(2 , 0);
			SplayTree.insert(90, 0);
			SplayTree.insert(3 , 0);
			SplayTree.insert(0 , 0);
			SplayTree.insert(14, 0);
			SplayTree.insert(45, 0);
			THEN("Test size") {
				REQUIRE(SplayTree.size() == 7);
			}
			THEN("Test height") {
				REQUIRE(SplayTree.height() == 5);
			}
			THEN("Test maximum") {
				auto max = SplayTree.maximum();
				REQUIRE(max != nullptr);
				REQUIRE(max->key == 90);
			}
			THEN("Test minimum") {
				auto min = SplayTree.minimum();
				REQUIRE(min != nullptr);
				REQUIRE(min->key == 0);
			}
			THEN("Test search for a node that does not exist") {
				auto result = SplayTree.search(1337);
				REQUIRE(result == nullptr);
			}
			THEN("Test search for a node that does exist") {
				auto result = SplayTree.search(3);
				REQUIRE(result != nullptr);
				REQUIRE(result->key == 3);
			}
		}
		WHEN("Nodes are inserted in ascending order") {
			for (int i = 0; i < 10; ++i) {
				SplayTree.insert(i, 0);
			}
			THEN("Test size") {
				REQUIRE(SplayTree.size() == 10);
			}
			THEN("Test height") {
				REQUIRE(SplayTree.height() == 10);
			}
			THEN("Test maximum") {
				auto max = SplayTree.maximum();
				REQUIRE(max != nullptr);
				REQUIRE(max->key == 9);
			}
			THEN("Test minimum") {
				auto min = SplayTree.minimum();
				REQUIRE(min != nullptr);
				REQUIRE(min->key == 0);
			}
			THEN("Test search for a node that does not exist") {
				auto result = SplayTree.search(1337);
				REQUIRE(result == nullptr);
			}
			THEN("Test search for a node that does exist") {
				auto result = SplayTree.search(3);
				REQUIRE(result != nullptr);
				REQUIRE(result->key == 3);
			}
		}
		WHEN("Nodes are inserted in descending order") {
			for (int i = 9; i >= 0; --i) {
				SplayTree.insert(i, 0);
			}
			THEN("Test size") {
				REQUIRE(SplayTree.size() == 10);
			}
			THEN("Test height") {
				REQUIRE(SplayTree.height() == 10);
			}
			THEN("Test maximum") {
				auto max = SplayTree.maximum();
				REQUIRE(max != nullptr);
				REQUIRE(max->key == 9);
			}
			THEN("Test minimum") {
				auto min = SplayTree.minimum();
				REQUIRE(min != nullptr);
				REQUIRE(min->key == 0);
			}
			THEN("Test search for a node that does not exist") {
				auto result = SplayTree.search(1337);
				REQUIRE(result == nullptr);
			}
			THEN("Test search for a node that does exist") {
				auto result = SplayTree.search(3);
				REQUIRE(result != nullptr);
				REQUIRE(result->key == 3);
			}
		}
	}
}
