/*
 * @file AVLTree.cpp
 * @author George Fotopoulos
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/AVLTree.hpp>

SCENARIO("Test AVL Tree") {
	GIVEN("An AVL Tree") {
		forest::AVLTree <int, int> AVLTree;
		WHEN("The AVL Tree is empty") {
			THEN("Test size") {
				REQUIRE(AVLTree.size() == 0);
			}
			THEN("Test height") {
				REQUIRE(AVLTree.height() == 0);
			}
			THEN("Test maximum") {
				auto max = AVLTree.maximum();
				REQUIRE(max == nullptr);
			}
			THEN("Test minimum") {
				auto min = AVLTree.minimum();
				REQUIRE(min == nullptr);
			}
			THEN("Test search for a node that does not exist") {
				auto result = AVLTree.search(555);
				REQUIRE(result == nullptr);
			}
		}
		WHEN("Nodes are inserted in random order") {
			AVLTree.insert(4 , 0);
			AVLTree.insert(2 , 0);
			AVLTree.insert(90, 0);
			AVLTree.insert(3 , 0);
			AVLTree.insert(0 , 0);
			AVLTree.insert(14, 0);
			AVLTree.insert(45, 0);
			THEN("Test size") {
				REQUIRE(AVLTree.size() == 7);
			}
			THEN("Test height") {
				REQUIRE(AVLTree.height() == 3);
			}
			THEN("Test maximum") {
				auto max = AVLTree.maximum();
				REQUIRE(max != nullptr);
				REQUIRE(max->key == 90);
			}
			THEN("Test minimum") {
				auto min = AVLTree.minimum();
				REQUIRE(min != nullptr);
				REQUIRE(min->key == 0);
			}
			THEN("Test search for a node that does not exist") {
				auto result = AVLTree.search(1337);
				REQUIRE(result == nullptr);
			}
			THEN("Test search for a node that does exist") {
				auto result = AVLTree.search(3);
				REQUIRE(result != nullptr);
				REQUIRE(result->key == 3);
			}
		}
		WHEN("Nodes are inserted in ascending order") {
			for (int i = 0; i < 10; i++) {
				AVLTree.insert(i, 0);
			}
			THEN("Test size") {
				REQUIRE(AVLTree.size() == 10);
			}
			THEN("Test height") {
				REQUIRE(AVLTree.height() == 4);
			}
			THEN("Test maximum") {
				auto max = AVLTree.maximum();
				REQUIRE(max != nullptr);
				REQUIRE(max->key == 9);
			}
			THEN("Test minimum") {
				auto min = AVLTree.minimum();
				REQUIRE(min != nullptr);
				REQUIRE(min->key == 0);
			}
			THEN("Test search for a node that does not exist") {
				auto result = AVLTree.search(1337);
				REQUIRE(result == nullptr);
			}
			THEN("Test search for a node that does exist") {
				auto result = AVLTree.search(3);
				REQUIRE(result != nullptr);
				REQUIRE(result->key == 3);
			}
		}
		WHEN("Nodes are inserted in descending order") {
			for (int i = 9; i >= 0; i--) {
				AVLTree.insert(i, 0);
			}
			THEN("Test size") {
				REQUIRE(AVLTree.size() == 10);
			}
			THEN("Test height") {
				REQUIRE(AVLTree.height() == 4);
			}
			THEN("Test maximum") {
				auto max = AVLTree.maximum();
				REQUIRE(max != nullptr);
				REQUIRE(max->key == 9);
			}
			THEN("Test minimum") {
				auto min = AVLTree.minimum();
				REQUIRE(min != nullptr);
				REQUIRE(min->key == 0);
			}
			THEN("Test search for a node that does not exist") {
				auto result = AVLTree.search(1337);
				REQUIRE(result == nullptr);
			}
			THEN("Test search for a node that does exist") {
				auto result = AVLTree.search(3);
				REQUIRE(result != nullptr);
				REQUIRE(result->key == 3);
			}
		}
	}
}
