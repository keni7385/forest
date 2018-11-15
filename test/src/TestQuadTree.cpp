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
#include <forest/QuadTree.hpp>

SCENARIO("Test Quad Tree") {
	GIVEN("A Quad Tree") {
		forest::QuadTree <float, 2> QuadTree({ {0, 0 }, { 10, 10 } });
		WHEN("The Quad Tree is empty") {
			THEN("Test search({ 0, 0 })") {
				REQUIRE(QuadTree.search({ 0, 0 }) == false);
			}
		}
		WHEN("Nodes are inserted in random order") {
			QuadTree.insert({ 1, 2 });
			QuadTree.insert({ -1, 1 });
			QuadTree.insert({ 3, 4 });
			QuadTree.insert({ -4, 3 });
			THEN("Test search({ 0, 0 })") {
				REQUIRE(QuadTree.search({ 0, 0 }) == false);
			}
			THEN("Test search({ -4, 3 })") {
				REQUIRE(QuadTree.search({ -4, 3 }) == true);
			}
			THEN("Test remove({ 1, 2 })") {
				REQUIRE(QuadTree.remove({ 1, 2 }) == true);
				REQUIRE(QuadTree.search({ 1, 2 }) == false);
			}
			THEN("Test clear()") {
				QuadTree.clear();
				REQUIRE(QuadTree.search({ 1, 2 }) == false);
				REQUIRE(QuadTree.search({ -1, 1 }) == false);
				REQUIRE(QuadTree.search({ 3, 4 }) == false);
				REQUIRE(QuadTree.search({ -4, 3 }) == false);
			}
		}
		WHEN("Nodes are inserted in ascending order") {
			for (float i = 0; i < 10; ++i) {
				QuadTree.insert({ i, i });
			}
			THEN("Test search({ -1, -1 })") {
				REQUIRE(QuadTree.search({ -1, -1 }) == false);
			}
			THEN("Test search({ 5, 5 })") {
				REQUIRE(QuadTree.search({ 5, 5 }) == true);
			}
			THEN("Test remove({ i, i })") {
				for (float i = 0; i < 4; ++i) {
					REQUIRE(QuadTree.remove({ i, i }) == true);
					REQUIRE(QuadTree.search({ i, i }) == false);
				}
			}
			THEN("Test clear()") {
				QuadTree.clear();
				for (float i = 0; i < 10; ++i) {
					REQUIRE(QuadTree.search({ i, i }) == false);
				}
			}
		}
		WHEN("Nodes are inserted in descending order") {
			for (float i = 9; i >= 0; --i) {
				QuadTree.insert({ i, i });
			}
			THEN("Test search({ -1, -1 })") {
				REQUIRE(QuadTree.search({ -1, -1 }) == false);
			}
			THEN("Test search({ 5, 5 })") {
				REQUIRE(QuadTree.search({ 5, 5 }) == true);
			}
			THEN("Test remove({ i, i })") {
				for (float i = 4; i >= 0; --i) {
					REQUIRE(QuadTree.remove({ i, i }) == true);
					REQUIRE(QuadTree.search({ i, i }) == false);
				}
			}
			THEN("Test clear()") {
				QuadTree.clear();
				for (float i = 9; i >= 0; --i) {
					REQUIRE(QuadTree.search({ i, i }) == false);
				}
			}
		}
	}
}
