/*
 * @file test_avltree.cpp
 * @author George Fotopoulos
 */

#include <catch2/catch.hpp>
#include <forest/avltree.hpp>
#include <string>

auto handler = [](const int & key, const int & value) {};

TEST_CASE("Test AVL Tree Duplicate Key Insertion") {
  forest::avltree <int, std::string> avltree;
  avltree.insert(0, "Thor");
  REQUIRE(avltree.search(0)->value == "Thor");
  avltree.insert(0, "Loki");
  REQUIRE(avltree.search(0)->value == "Loki");
}

TEST_CASE("Test AVL Tree Constructor") {
  forest::avltree <int, std::string> avltree({
    {2 , "Thor"},
    {4 , "Odin"},
    {90, "Loki"},
    {3 , "Baldr"},
    {0 , "Frigg"},
    {14, "Eir"},
    {45, "Heimdall"}
  });
  REQUIRE(avltree.search(2 )->value == "Thor");
  REQUIRE(avltree.search(4 )->value == "Odin");
  REQUIRE(avltree.search(90)->value == "Loki");
  REQUIRE(avltree.search(3 )->value == "Baldr");
  REQUIRE(avltree.search(0 )->value == "Frigg");
  REQUIRE(avltree.search(14)->value == "Eir");
  REQUIRE(avltree.search(45)->value == "Heimdall");
}

SCENARIO("Test AVL Tree") {
  GIVEN("An AVL Tree") {
    forest::avltree <int, int> avltree;
    WHEN("The AVL Tree is empty") {
      THEN("Test root") {
        REQUIRE(avltree.root() == nullptr);
      }
      THEN("Test empty") {
        REQUIRE(avltree.empty() == true);
      }
      THEN("Test size") {
        REQUIRE(avltree.size() == 0);
      }
      THEN("Test height") {
        REQUIRE(avltree.height() == 0);
      }
      THEN("Test maximum") {
        auto max = avltree.maximum();
        REQUIRE(max == nullptr);
      }
      THEN("Test minimum") {
        auto min = avltree.minimum();
        REQUIRE(min == nullptr);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = avltree.predecessor(1911);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = avltree.successor(1337);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = avltree.search(555);
        REQUIRE(result == nullptr);
      }
      THEN("Call pre_order_traversal") {
        avltree.pre_order_traversal(handler);
      }
      THEN("Call in_order_traversal") {
        avltree.in_order_traversal(handler);
      }
      THEN("Call post_order_traversal") {
        avltree.post_order_traversal(handler);
      }
    }
    WHEN("Nodes are inserted in random order") {
      avltree.insert(4 , 0);
      avltree.insert(2 , 0);
      avltree.insert(90, 0);
      avltree.insert(3 , 0);
      avltree.insert(0 , 0);
      avltree.insert(14, 0);
      avltree.insert(45, 0);
      THEN("Test root") {
        auto root = avltree.root();
        REQUIRE(root != nullptr);
        REQUIRE(root->key == 4);
      }
      THEN("Test empty") {
        REQUIRE(avltree.empty() == false);
      }
      THEN("Test size") {
        REQUIRE(avltree.size() == 7);
      }
      THEN("Test height") {
        REQUIRE(avltree.height() == 3);
      }
      THEN("Test maximum") {
        auto max = avltree.maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 90);
      }
      THEN("Test minimum") {
        auto min = avltree.minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test predecessor for a node that does exist") {
        auto predecessor = avltree.predecessor(90);
        REQUIRE(predecessor != nullptr);
        REQUIRE(predecessor->key == 45);
      }
      THEN("Test successor for a node that does exist") {
        auto successor = avltree.successor(0);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->key == 2);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = avltree.predecessor(1917);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = avltree.successor(1920);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = avltree.search(1337);
        REQUIRE(result == nullptr);
      }
      THEN("Test search for a node that does exist") {
        auto result = avltree.search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Call pre_order_traversal") {
        avltree.pre_order_traversal(handler);
      }
      THEN("Call in_order_traversal") {
        avltree.in_order_traversal(handler);
      }
      THEN("Call post_order_traversal") {
        avltree.post_order_traversal(handler);
      }
    }
    WHEN("Nodes are inserted in ascending order") {
      for (int i = 0; i < 10; i++) {
        avltree.insert(i, 0);
      }
      THEN("Test root") {
        auto root = avltree.root();
        REQUIRE(root != nullptr);
        REQUIRE(root->key == 3);
      }
      THEN("Test empty") {
        REQUIRE(avltree.empty() == false);
      }
      THEN("Test size") {
        REQUIRE(avltree.size() == 10);
      }
      THEN("Test height") {
        REQUIRE(avltree.height() == 4);
      }
      THEN("Test maximum") {
        auto max = avltree.maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 9);
      }
      THEN("Test minimum") {
        auto min = avltree.minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test predecessor for a node that does exist") {
        auto predecessor = avltree.predecessor(9);
        REQUIRE(predecessor != nullptr);
        REQUIRE(predecessor->key == 8);
      }
      THEN("Test successor for a node that does exist") {
        auto successor = avltree.successor(3);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->key == 4);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = avltree.predecessor(1917);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = avltree.successor(1920);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = avltree.search(1337);
        REQUIRE(result == nullptr);
      }
      THEN("Test search for a node that does exist") {
        auto result = avltree.search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Call pre_order_traversal") {
        avltree.pre_order_traversal(handler);
      }
      THEN("Call in_order_traversal") {
        avltree.in_order_traversal(handler);
      }
      THEN("Call post_order_traversal") {
        avltree.post_order_traversal(handler);
      }
    }
    WHEN("Nodes are inserted in descending order") {
      for (int i = 9; i >= 0; i--) {
        avltree.insert(i, 0);
      }
      THEN("Test root") {
        auto root = avltree.root();
        REQUIRE(root != nullptr);
        REQUIRE(root->key == 6);
      }
      THEN("Test empty") {
        REQUIRE(avltree.empty() == false);
      }
      THEN("Test size") {
        REQUIRE(avltree.size() == 10);
      }
      THEN("Test height") {
        REQUIRE(avltree.height() == 4);
      }
      THEN("Test maximum") {
        auto max = avltree.maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 9);
      }
      THEN("Test minimum") {
        auto min = avltree.minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test predecessor for a node that does exist") {
        auto predecessor = avltree.predecessor(9);
        REQUIRE(predecessor != nullptr);
        REQUIRE(predecessor->key == 8);
      }
      THEN("Test successor for a node that does exist") {
        auto successor = avltree.successor(3);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->key == 4);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = avltree.predecessor(1917);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = avltree.successor(1920);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = avltree.search(1337);
        REQUIRE(result == nullptr);
      }
      THEN("Test search for a node that does exist") {
        auto result = avltree.search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Call pre_order_traversal") {
        avltree.pre_order_traversal(handler);
      }
      THEN("Call in_order_traversal") {
        avltree.in_order_traversal(handler);
      }
      THEN("Call post_order_traversal") {
        avltree.post_order_traversal(handler);
      }
    }
  }
}
