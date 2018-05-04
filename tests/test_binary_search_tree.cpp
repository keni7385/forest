#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <forest/binary_search_tree.h>

SCENARIO("Test Binary Search Tree") {
  GIVEN("A Binary Search Tree") {
    forest::binary_search_tree <int, int> binary_search_tree;
    WHEN("The Binary Search Tree is empty") {
      THEN("Test empty") {
        REQUIRE(binary_search_tree.empty() == true);
      }
      THEN("Test size") {
        REQUIRE(binary_search_tree.size() == 0);
      }
      THEN("Test height") {
        REQUIRE(binary_search_tree.height() == 0);
      }
      THEN("Test maximum") {
        auto max = binary_search_tree.maximum();
        REQUIRE(max == nullptr);
      }
      THEN("Test minimum") {
        auto min = binary_search_tree.minimum();
        REQUIRE(min == nullptr);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = binary_search_tree.predecessor(1911);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = binary_search_tree.successor(1337);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = binary_search_tree.search(555);
        REQUIRE(result == nullptr);
      }
    }
    WHEN("Nodes are inserted in random order") {
      binary_search_tree.insert(4 , 0);
      binary_search_tree.insert(2 , 0);
      binary_search_tree.insert(90, 0);
      binary_search_tree.insert(3 , 0);
      binary_search_tree.insert(0 , 0);
      binary_search_tree.insert(14, 0);
      binary_search_tree.insert(45, 0);
      THEN("Test empty") {
        REQUIRE(binary_search_tree.empty() == false);
      }
      THEN("Test size") {
        REQUIRE(binary_search_tree.size() == 7);
      }
      THEN("Test height") {
        REQUIRE(binary_search_tree.height() == 4);
      }
      THEN("Test maximum") {
        auto max = binary_search_tree.maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 90);
      }
      THEN("Test minimum") {
        auto min = binary_search_tree.minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test predecessor for a node that does exist") {
        auto predecessor = binary_search_tree.predecessor(90);
        REQUIRE(predecessor != nullptr);
        REQUIRE(predecessor->key == 45);
      }
      THEN("Test successor for a node that does exist") {
        auto successor = binary_search_tree.successor(0);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->key == 2);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = binary_search_tree.predecessor(1917);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = binary_search_tree.successor(1920);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = binary_search_tree.search(1337);
        REQUIRE(result == nullptr);
      }
      THEN("Test search for a node that does exist") {
        auto result = binary_search_tree.search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
    }
    WHEN("Nodes are inserted in ascending order") {
      for (int i = 0; i < 10; i++) {
        binary_search_tree.insert(i, 0);
      }
      THEN("Test empty") {
        REQUIRE(binary_search_tree.empty() == false);
      }
      THEN("Test size") {
        REQUIRE(binary_search_tree.size() == 10);
      }
      THEN("Test height") {
        REQUIRE(binary_search_tree.height() == 10);
      }
      THEN("Test maximum") {
        auto max = binary_search_tree.maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 9);
      }
      THEN("Test minimum") {
        auto min = binary_search_tree.minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test predecessor for a node that does exist") {
        auto predecessor = binary_search_tree.predecessor(9);
        REQUIRE(predecessor != nullptr);
        REQUIRE(predecessor->key == 8);
      }
      THEN("Test successor for a node that does exist") {
        auto successor = binary_search_tree.successor(3);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->key == 4);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = binary_search_tree.predecessor(1917);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = binary_search_tree.successor(1920);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = binary_search_tree.search(1337);
        REQUIRE(result == nullptr);
      }
      THEN("Test search for a node that does exist") {
        auto result = binary_search_tree.search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
    }
    WHEN("Nodes are inserted in descending order") {
      for (int i = 9; i >= 0; i--) {
        binary_search_tree.insert(i, 0);
      }
      THEN("Test empty") {
        REQUIRE(binary_search_tree.empty() == false);
      }
      THEN("Test size") {
        REQUIRE(binary_search_tree.size() == 10);
      }
      THEN("Test height") {
        REQUIRE(binary_search_tree.height() == 10);
      }
      THEN("Test maximum") {
        auto max = binary_search_tree.maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 9);
      }
      THEN("Test minimum") {
        auto min = binary_search_tree.minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test predecessor for a node that does exist") {
        auto predecessor = binary_search_tree.predecessor(9);
        REQUIRE(predecessor != nullptr);
        REQUIRE(predecessor->key == 8);
      }
      THEN("Test successor for a node that does exist") {
        auto successor = binary_search_tree.successor(3);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->key == 4);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = binary_search_tree.predecessor(1917);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = binary_search_tree.successor(1920);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = binary_search_tree.search(1337);
        REQUIRE(result == nullptr);
      }
      THEN("Test search for a node that does exist") {
        auto result = binary_search_tree.search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
    }
  }
}
