/*
 * @file RedBlackTree.cpp
 * @author George Fotopoulos
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/RedBlackTree.hpp>

SCENARIO("Test Red Black Tree") {
	GIVEN("A Red Black Tree") {
		forest::RedBlackTree <int, int> RedBlackTree;
		WHEN("The Red Black Tree is empty") {
			THEN("Test size") {
				REQUIRE(RedBlackTree.size() == 0);
			}
			THEN("Test height") {
				REQUIRE(RedBlackTree.height() == 0);
			}
			THEN("Test maximum") {
				auto max = RedBlackTree.maximum();
				REQUIRE(max == nullptr);
			}
			THEN("Test minimum") {
				auto min = RedBlackTree.minimum();
				REQUIRE(min == nullptr);
			}
			THEN("Test search for a node that does not exist") {
				auto result = RedBlackTree.search(555);
				REQUIRE(result == nullptr);
			}
		}
		WHEN("Nodes are inserted in random order") {
			RedBlackTree.insert(4 , 0);
			RedBlackTree.insert(2 , 0);
			RedBlackTree.insert(90, 0);
			RedBlackTree.insert(3 , 0);
			RedBlackTree.insert(0 , 0);
			RedBlackTree.insert(14, 0);
			RedBlackTree.insert(45, 0);
			THEN("Test size") {
				REQUIRE(RedBlackTree.size() == 7);
			}
			THEN("Test height") {
				REQUIRE(RedBlackTree.height() == 3);
			}
			THEN("Test maximum") {
				auto max = RedBlackTree.maximum();
				REQUIRE(max != nullptr);
				REQUIRE(max->key == 90);
			}
			THEN("Test minimum") {
				auto min = RedBlackTree.minimum();
				REQUIRE(min != nullptr);
				REQUIRE(min->key == 0);
			}
			THEN("Test search for a node that does not exist") {
				auto result = RedBlackTree.search(1337);
				REQUIRE(result == nullptr);
			}
			THEN("Test search for a node that does exist") {
				auto result = RedBlackTree.search(3);
				REQUIRE(result != nullptr);
				REQUIRE(result->key == 3);
			}
		}
		WHEN("Nodes are inserted in ascending order") {
			for (int i = 0; i < 10; i++) {
				RedBlackTree.insert(i, 0);
			}
			THEN("Test size") {
				REQUIRE(RedBlackTree.size() == 10);
			}
			THEN("Test height") {
				REQUIRE(RedBlackTree.height() == 5);
			}
			THEN("Test maximum") {
				auto max = RedBlackTree.maximum();
				REQUIRE(max != nullptr);
				REQUIRE(max->key == 9);
			}
			THEN("Test minimum") {
				auto min = RedBlackTree.minimum();
				REQUIRE(min != nullptr);
				REQUIRE(min->key == 0);
			}
			THEN("Test search for a node that does not exist") {
				auto result = RedBlackTree.search(1337);
				REQUIRE(result == nullptr);
			}
			THEN("Test search for a node that does exist") {
				auto result = RedBlackTree.search(3);
				REQUIRE(result != nullptr);
				REQUIRE(result->key == 3);
			}
		}
		WHEN("Nodes are inserted in descending order") {
			for (int i = 9; i >= 0; i--) {
				RedBlackTree.insert(i, 0);
			}
			THEN("Test size") {
				REQUIRE(RedBlackTree.size() == 10);
			}
			THEN("Test height") {
				REQUIRE(RedBlackTree.height() == 5);
			}
			THEN("Test maximum") {
				auto max = RedBlackTree.maximum();
				REQUIRE(max != nullptr);
				REQUIRE(max->key == 9);
			}
			THEN("Test minimum") {
				auto min = RedBlackTree.minimum();
				REQUIRE(min != nullptr);
				REQUIRE(min->key == 0);
			}
			THEN("Test search for a node that does not exist") {
				auto result = RedBlackTree.search(1337);
				REQUIRE(result == nullptr);
			}
			THEN("Test search for a node that does exist") {
				auto result = RedBlackTree.search(3);
				REQUIRE(result != nullptr);
				REQUIRE(result->key == 3);
			}
		}
	}
}
