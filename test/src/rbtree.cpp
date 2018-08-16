#include <catch2/catch.hpp>
#include <forest/rbtree.hpp>
#include <string>

auto handler = [](const int & key, const int & value) {};

TEST_CASE("Test Red Black Tree Constructor") {
  forest::rbtree <int, std::string> rbtree({
    {2 , "Thor"},
    {4 , "Odin"},
    {90, "Loki"},
    {3 , "Baldr"},
    {0 , "Frigg"},
    {14, "Eir"},
    {45, "Heimdall"}
  });
  REQUIRE(rbtree.search(2 )->value == "Thor");
  REQUIRE(rbtree.search(4 )->value == "Odin");
  REQUIRE(rbtree.search(90)->value == "Loki");
  REQUIRE(rbtree.search(3 )->value == "Baldr");
  REQUIRE(rbtree.search(0 )->value == "Frigg");
  REQUIRE(rbtree.search(14)->value == "Eir");
  REQUIRE(rbtree.search(45)->value == "Heimdall");
}

SCENARIO("Test Red Black Tree") {
  GIVEN("A Red Black Tree") {
    forest::rbtree <int, int> rbtree;
    WHEN("The Red Black Tree is empty") {
      THEN("Test root") {
        REQUIRE(rbtree.root() == nullptr);
      }
      THEN("Test empty") {
        REQUIRE(rbtree.empty() == true);
      }
      THEN("Test size") {
        REQUIRE(rbtree.size() == 0);
      }
      THEN("Test height") {
        REQUIRE(rbtree.height() == 0);
      }
      THEN("Test maximum") {
        auto max = rbtree.maximum();
        REQUIRE(max == nullptr);
      }
      THEN("Test minimum") {
        auto min = rbtree.minimum();
        REQUIRE(min == nullptr);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = rbtree.predecessor(1911);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = rbtree.successor(1337);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = rbtree.search(555);
        REQUIRE(result == nullptr);
      }
      THEN("Call pre_order_traversal") {
        rbtree.pre_order_traversal(handler);
      }
      THEN("Call in_order_traversal") {
        rbtree.in_order_traversal(handler);
      }
      THEN("Call post_order_traversal") {
        rbtree.post_order_traversal(handler);
      }
    }
    WHEN("Nodes are inserted in random order") {
      rbtree.insert(4 , 0);
      rbtree.insert(2 , 0);
      rbtree.insert(90, 0);
      rbtree.insert(3 , 0);
      rbtree.insert(0 , 0);
      rbtree.insert(14, 0);
      rbtree.insert(45, 0);
      THEN("Test root") {
        auto root = rbtree.root();
        REQUIRE(root != nullptr);
        REQUIRE(root->key == 4);
      }
      THEN("Test empty") {
        REQUIRE(rbtree.empty() == false);
      }
      THEN("Test size") {
        REQUIRE(rbtree.size() == 7);
      }
      THEN("Test height") {
        REQUIRE(rbtree.height() == 3);
      }
      THEN("Test maximum") {
        auto max = rbtree.maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 90);
      }
      THEN("Test minimum") {
        auto min = rbtree.minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test predecessor for a node that does exist") {
        auto predecessor = rbtree.predecessor(90);
        REQUIRE(predecessor != nullptr);
        REQUIRE(predecessor->key == 45);
      }
      THEN("Test successor for a node that does exist") {
        auto successor = rbtree.successor(0);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->key == 2);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = rbtree.predecessor(1917);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = rbtree.successor(1920);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = rbtree.search(1337);
        REQUIRE(result == nullptr);
      }
      THEN("Test search for a node that does exist") {
        auto result = rbtree.search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Call pre_order_traversal") {
        rbtree.pre_order_traversal(handler);
      }
      THEN("Call in_order_traversal") {
        rbtree.in_order_traversal(handler);
      }
      THEN("Call post_order_traversal") {
        rbtree.post_order_traversal(handler);
      }
    }
    WHEN("Nodes are inserted in ascending order") {
      for (int i = 0; i < 10; i++) {
        rbtree.insert(i, 0);
      }
      THEN("Test root") {
        auto root = rbtree.root();
        REQUIRE(root != nullptr);
        REQUIRE(root->key == 3);
      }
      THEN("Test empty") {
        REQUIRE(rbtree.empty() == false);
      }
      THEN("Test size") {
        REQUIRE(rbtree.size() == 10);
      }
      THEN("Test height") {
        REQUIRE(rbtree.height() == 5);
      }
      THEN("Test maximum") {
        auto max = rbtree.maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 9);
      }
      THEN("Test minimum") {
        auto min = rbtree.minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test predecessor for a node that does exist") {
        auto predecessor = rbtree.predecessor(9);
        REQUIRE(predecessor != nullptr);
        REQUIRE(predecessor->key == 8);
      }
      THEN("Test successor for a node that does exist") {
        auto successor = rbtree.successor(3);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->key == 4);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = rbtree.predecessor(1917);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = rbtree.successor(1920);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = rbtree.search(1337);
        REQUIRE(result == nullptr);
      }
      THEN("Test search for a node that does exist") {
        auto result = rbtree.search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Call pre_order_traversal") {
        rbtree.pre_order_traversal(handler);
      }
      THEN("Call in_order_traversal") {
        rbtree.in_order_traversal(handler);
      }
      THEN("Call post_order_traversal") {
        rbtree.post_order_traversal(handler);
      }
    }
    WHEN("Nodes are inserted in descending order") {
      for (int i = 9; i >= 0; i--) {
        rbtree.insert(i, 0);
      }
      THEN("Test root") {
        auto root = rbtree.root();
        REQUIRE(root != nullptr);
        REQUIRE(root->key == 6);
      }
      THEN("Test empty") {
        REQUIRE(rbtree.empty() == false);
      }
      THEN("Test size") {
        REQUIRE(rbtree.size() == 10);
      }
      THEN("Test height") {
        REQUIRE(rbtree.height() == 5);
      }
      THEN("Test maximum") {
        auto max = rbtree.maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 9);
      }
      THEN("Test minimum") {
        auto min = rbtree.minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test predecessor for a node that does exist") {
        auto predecessor = rbtree.predecessor(9);
        REQUIRE(predecessor != nullptr);
        REQUIRE(predecessor->key == 8);
      }
      THEN("Test successor for a node that does exist") {
        auto successor = rbtree.successor(3);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->key == 4);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = rbtree.predecessor(1917);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = rbtree.successor(1920);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = rbtree.search(1337);
        REQUIRE(result == nullptr);
      }
      THEN("Test search for a node that does exist") {
        auto result = rbtree.search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Call pre_order_traversal") {
        rbtree.pre_order_traversal(handler);
      }
      THEN("Call in_order_traversal") {
        rbtree.in_order_traversal(handler);
      }
      THEN("Call post_order_traversal") {
        rbtree.post_order_traversal(handler);
      }
    }
  }
}
