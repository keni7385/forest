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
		forest::KDTree<float, 2>KDTree;
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
				REQUIRE(KDTree.search({ 0, 0 }) == false);
			}
			THEN("Test remove({ 0 , 0 })") {
				KDTree.remove({ 0, 0 });
				REQUIRE(KDTree.search({ 0, 0 }) == false);
			}
			THEN("Test clear()") {
				KDTree.clear();
				REQUIRE(KDTree.size() == 0);
			}
			THEN("Test query({ { 0 , 0 }, { 1, 1 } })") {
				forest::KDTree<float, 2>::Points results;
				KDTree.query({ { 0 , 0 }, { 1, 1 } }, [&results](auto point) {
					results.push_back(point);
				});
				REQUIRE(results.empty() == true);
			}
		}
		WHEN("Nodes are inserted in random order") {
			forest::KDTree<float, 2>::Points points{
				{ -3,  3 },
				{ -2,  2 },
				{ -1,  1 },
				{  0,  0 },
				{  1, -1 },
				{  2, -2 },
				{  3, -3 }
			};
			KDTree.fill(points.begin(), points.end());
			THEN("Test size()") {
				REQUIRE(KDTree.size() == 7);
			}
			THEN("Test maximum(0)") {
				auto max = KDTree.maximum(0);
				REQUIRE(max != nullptr);
				REQUIRE(max->point[0] == 3);
				REQUIRE(max->point[1] == -3);
			}
			THEN("Test minimum(0)") {
				auto min = KDTree.minimum(0);
				REQUIRE(min != nullptr);
				REQUIRE(min->point[0] == -3);
				REQUIRE(min->point[1] == 3);
			}
			THEN("Test maximum(1)") {
				auto max = KDTree.maximum(1);
				REQUIRE(max != nullptr);
				REQUIRE(max->point[0] == -3);
				REQUIRE(max->point[1] == 3);
			}
			THEN("Test minimum(1)") {
				auto min = KDTree.minimum(1);
				REQUIRE(min != nullptr);
				REQUIRE(min->point[0] == 3);
				REQUIRE(min->point[1] == -3);
			}
			THEN("Test search({ 0, 0 })") {
				REQUIRE(KDTree.search({ 0, 0 }) == true);
			}
			THEN("Test search({ 2, -2 })") {
				REQUIRE(KDTree.search({ 2, -2 }) != false);
			}
			THEN("Test remove({ 0 , 0 })") {
				KDTree.remove({ 0, 0 });
				REQUIRE(KDTree.search({ 0, 0 }) == false);
			}
			THEN("Test remove({ -3 , 3 })") {
				KDTree.remove({ -3, 3 });
				REQUIRE(KDTree.search({ -3, 3 }) == false);
			}
			THEN("Test remove({ 3 , -3 })") {
				KDTree.remove({ 3, -3 });
				REQUIRE(KDTree.search({ 3, -3 }) == false);
			}
			THEN("Test clear()") {
				KDTree.clear();
				REQUIRE(KDTree.size() == 0);
			}
			THEN("Test query({ { 0 , 0 }, { 5, 5 } })") {
				forest::KDTree<float, 2>::Points results;
				KDTree.query({ { 0 , 0 }, { 5, 5 } }, [&results](auto point) {
					results.push_back(point);
				});
				REQUIRE(results.size() == 7);
			}
		}
	}
}
