/*
 * @file BinarySearchTree.cpp
 * @author George Fotopoulos
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/BinarySearchTree.hpp>

SCENARIO("Test Binary Search Tree") {
	GIVEN("A Binary Search Tree") {
		forest::BinarySearchTree <int, int> BinarySearchTree;
		WHEN("The Binary Search Tree is empty") {
			THEN("Test maximum") {
				auto max = BinarySearchTree.maximum();
				REQUIRE(max == nullptr);
			}
			THEN("Test minimum") {
				auto min = BinarySearchTree.minimum();
				REQUIRE(min == nullptr);
			}
			THEN("Test search for a node that does not exist") {
				auto result = BinarySearchTree.search(555);
				REQUIRE(result == nullptr);
			}
		}
		WHEN("Nodes are inserted in random order") {
			BinarySearchTree.insert(4 , 0);
			BinarySearchTree.insert(2 , 0);
			BinarySearchTree.insert(90, 0);
			BinarySearchTree.insert(3 , 0);
			BinarySearchTree.insert(0 , 0);
			BinarySearchTree.insert(14, 0);
			BinarySearchTree.insert(45, 0);
			THEN("Test maximum") {
				auto max = BinarySearchTree.maximum();
				REQUIRE(max != nullptr);
				REQUIRE(max->key == 90);
			}
			THEN("Test minimum") {
				auto min = BinarySearchTree.minimum();
				REQUIRE(min != nullptr);
				REQUIRE(min->key == 0);
			}
			THEN("Test search for a node that does not exist") {
				auto result = BinarySearchTree.search(1337);
				REQUIRE(result == nullptr);
			}
			THEN("Test search for a node that does exist") {
				auto result = BinarySearchTree.search(3);
				REQUIRE(result != nullptr);
				REQUIRE(result->key == 3);
			}
		}
		WHEN("Nodes are inserted in ascending order") {
			for (int i = 0; i < 10; i++) {
				BinarySearchTree.insert(i, 0);
			}
			THEN("Test maximum") {
				auto max = BinarySearchTree.maximum();
				REQUIRE(max != nullptr);
				REQUIRE(max->key == 9);
			}
			THEN("Test minimum") {
				auto min = BinarySearchTree.minimum();
				REQUIRE(min != nullptr);
				REQUIRE(min->key == 0);
			}
			THEN("Test search for a node that does not exist") {
				auto result = BinarySearchTree.search(1337);
				REQUIRE(result == nullptr);
			}
			THEN("Test search for a node that does exist") {
				auto result = BinarySearchTree.search(3);
				REQUIRE(result != nullptr);
				REQUIRE(result->key == 3);
			}
		}
		WHEN("Nodes are inserted in descending order") {
			for (int i = 9; i >= 0; i--) {
				BinarySearchTree.insert(i, 0);
			}
			THEN("Test maximum") {
				auto max = BinarySearchTree.maximum();
				REQUIRE(max != nullptr);
				REQUIRE(max->key == 9);
			}
			THEN("Test minimum") {
				auto min = BinarySearchTree.minimum();
				REQUIRE(min != nullptr);
				REQUIRE(min->key == 0);
			}
			THEN("Test search for a node that does not exist") {
				auto result = BinarySearchTree.search(1337);
				REQUIRE(result == nullptr);
			}
			THEN("Test search for a node that does exist") {
				auto result = BinarySearchTree.search(3);
				REQUIRE(result != nullptr);
				REQUIRE(result->key == 3);
			}
		}
	}
}
