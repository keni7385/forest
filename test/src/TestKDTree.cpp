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
#include <forest/KDTree.hpp>

SCENARIO("Test KD Tree") {
	GIVEN("A KD Tree") {
		forest::KDTree <float, 2> KDTree;
		WHEN("The KD Tree is empty") {
			THEN("Test size()") {
				REQUIRE(KDTree.size() == 0);
			}
			THEN("Test maximum(0)") {
				REQUIRE(KDTree.maximum(0) == nullptr);
			}
			THEN("Test minimum(0)") {
				REQUIRE(KDTree.minimum(0) == nullptr);
			}
			THEN("Test search({ 0, 0 })") {
				REQUIRE(KDTree.search({ 0, 0 }) == nullptr);
			}
			THEN("Test clear()") {
				KDTree.clear();
				REQUIRE(KDTree.size() == 0);
			}
		}
		WHEN("Nodes are inserted in random order") {
			KDTree.insert({ 1, 2 });
			KDTree.insert({ -1, 1 });
			KDTree.insert({ 3, 4 });
			KDTree.insert({ -4, 3 });
			THEN("Test size()") {
				REQUIRE(KDTree.size() == 4);
			}
			THEN("Test maximum(0)") {
				auto max = KDTree.maximum(0);
				REQUIRE(max != nullptr);
				REQUIRE(max->point[0] == 3);
				REQUIRE(max->point[1] == 4);
			}
			THEN("Test minimum(0)") {
				auto min = KDTree.minimum(0);
				REQUIRE(min != nullptr);
				REQUIRE(min->point[0] == -4);
				REQUIRE(min->point[1] == 3);
			}
			THEN("Test search({ 0, 0 })") {
				REQUIRE(KDTree.search({ 0, 0 }) == nullptr);
			}
			THEN("Test search({ -4, 3 })") {
				auto result = KDTree.search({ -4, 3 });
				REQUIRE(result != nullptr);
				REQUIRE(result->point[0] == -4);
				REQUIRE(result->point[1] == 3);
			}
			THEN("Test clear()") {
				KDTree.clear();
				REQUIRE(KDTree.size() == 0);
			}
		}
		WHEN("Nodes are inserted in ascending order") {
			for (float i = 0; i < 10; ++i) {
				KDTree.insert({ i, i });
			}
			THEN("Test size()") {
				REQUIRE(KDTree.size() == 10);
			}
			THEN("Test maximum(0)") {
				auto max = KDTree.maximum(0);
				REQUIRE(max != nullptr);
				REQUIRE(max->point[0] == 9);
				REQUIRE(max->point[1] == 9);
			}
			THEN("Test minimum(0)") {
				auto min = KDTree.minimum(0);
				REQUIRE(min != nullptr);
				REQUIRE(min->point[0] == 0);
				REQUIRE(min->point[1] == 0);
			}
			THEN("Test search({ -1, -1 })") {
				REQUIRE(KDTree.search({ -1, -1 }) == nullptr);
			}
			THEN("Test search({ 5, 5 })") {
				auto result = KDTree.search({ 5, 5 });
				REQUIRE(result != nullptr);
				REQUIRE(result->point[0] == 5);
				REQUIRE(result->point[1] == 5);
			}
			THEN("Test clear()") {
				KDTree.clear();
				REQUIRE(KDTree.size() == 0);
			}
		}
		WHEN("Nodes are inserted in descending order") {
			for (float i = 9; i >= 0; --i) {
				KDTree.insert({ i, i });
			}
			THEN("Test size()") {
				REQUIRE(KDTree.size() == 10);
			}
			THEN("Test maximum(0)") {
				auto max = KDTree.maximum(0);
				REQUIRE(max != nullptr);
				REQUIRE(max->point[0] == 9);
				REQUIRE(max->point[1] == 9);
			}
			THEN("Test minimum(0)") {
				auto min = KDTree.minimum(0);
				REQUIRE(min != nullptr);
				REQUIRE(min->point[0] == 0);
				REQUIRE(min->point[1] == 0);
			}
			THEN("Test search({ -1, -1 })") {
				REQUIRE(KDTree.search({ -1, -1 }) == nullptr);
			}
			THEN("Test search({ 5, 5 })") {
				auto result = KDTree.search({ 5, 5 });
				REQUIRE(result != nullptr);
				REQUIRE(result->point[0] == 5);
				REQUIRE(result->point[1] == 5);
			}
			THEN("Test clear()") {
				KDTree.clear();
				REQUIRE(KDTree.size() == 0);
			}
		}
	}
}
