#include <catch.hpp>
#include <forest/splaytree.hpp>
#include <string>

TEST_CASE("Test Splay Tree Constructor") {
  forest::splaytree <int, std::string> splaytree({
    {2 , "Thor"},
    {4 , "Odin"},
    {90, "Loki"},
    {3 , "Baldr"},
    {0 , "Frigg"},
    {14, "Eir"},
    {45, "Heimdall"}
  });
  REQUIRE(splaytree.search(2 )->value == "Thor");
  REQUIRE(splaytree.search(4 )->value == "Odin");
  REQUIRE(splaytree.search(90)->value == "Loki");
  REQUIRE(splaytree.search(3 )->value == "Baldr");
  REQUIRE(splaytree.search(0 )->value == "Frigg");
  REQUIRE(splaytree.search(14)->value == "Eir");
  REQUIRE(splaytree.search(45)->value == "Heimdall");
}

SCENARIO("Test Splay Tree") {
  GIVEN("A Splay Tree") {
    forest::splaytree <int, int> splaytree;
    WHEN("The Splay Tree is empty") {
      THEN("Test root") {
        REQUIRE(splaytree.root() == nullptr);
      }
      THEN("Test empty") {
        REQUIRE(splaytree.empty() == true);
      }
      THEN("Test size") {
        REQUIRE(splaytree.size() == 0);
      }
      THEN("Test height") {
        REQUIRE(splaytree.height() == 0);
      }
      THEN("Test maximum") {
        auto max = splaytree.maximum();
        REQUIRE(max == nullptr);
      }
      THEN("Test minimum") {
        auto min = splaytree.minimum();
        REQUIRE(min == nullptr);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = splaytree.predecessor(1911);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = splaytree.successor(1337);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = splaytree.search(555);
        REQUIRE(result == nullptr);
      }
      THEN("Call pre_order_traversal") {
        splaytree.pre_order_traversal([](auto key, auto value) {});
      }
      THEN("Call in_order_traversal") {
        splaytree.in_order_traversal([](auto key, auto value) {});
      }
      THEN("Call post_order_traversal") {
        splaytree.post_order_traversal([](auto key, auto value) {});
      }
    }
    WHEN("Nodes are inserted in random order") {
      splaytree.insert(4 , 0);
      splaytree.insert(2 , 0);
      splaytree.insert(90, 0);
      splaytree.insert(3 , 0);
      splaytree.insert(0 , 0);
      splaytree.insert(14, 0);
      splaytree.insert(45, 0);
      THEN("Test root") {
        auto root = splaytree.root();
        REQUIRE(root != nullptr);
        REQUIRE(root->key == 45);
      }
      THEN("Test empty") {
        REQUIRE(splaytree.empty() == false);
      }
      THEN("Test size") {
        REQUIRE(splaytree.size() == 7);
      }
      THEN("Test height") {
        REQUIRE(splaytree.height() == 5);
      }
      THEN("Test maximum") {
        auto max = splaytree.maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 90);
      }
      THEN("Test minimum") {
        auto min = splaytree.minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test predecessor for a node that does exist") {
        auto predecessor = splaytree.predecessor(90);
        REQUIRE(predecessor != nullptr);
        REQUIRE(predecessor->key == 45);
      }
      THEN("Test successor for a node that does exist") {
        auto successor = splaytree.successor(0);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->key == 2);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = splaytree.predecessor(1917);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = splaytree.successor(1920);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = splaytree.search(1337);
        REQUIRE(result == nullptr);
      }
      THEN("Test search for a node that does exist") {
        auto result = splaytree.search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Call pre_order_traversal") {
        splaytree.pre_order_traversal([](auto key, auto value) {});
      }
      THEN("Call in_order_traversal") {
        splaytree.in_order_traversal([](auto key, auto value) {});
      }
      THEN("Call post_order_traversal") {
        splaytree.post_order_traversal([](auto key, auto value) {});
      }
    }
    WHEN("Nodes are inserted in ascending order") {
      for (int i = 0; i < 10; i++) {
        splaytree.insert(i, 0);
      }
      THEN("Test root") {
        auto root = splaytree.root();
        REQUIRE(root != nullptr);
        REQUIRE(root->key == 9);
      }
      THEN("Test empty") {
        REQUIRE(splaytree.empty() == false);
      }
      THEN("Test size") {
        REQUIRE(splaytree.size() == 10);
      }
      THEN("Test height") {
        REQUIRE(splaytree.height() == 10);
      }
      THEN("Test maximum") {
        auto max = splaytree.maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 9);
      }
      THEN("Test minimum") {
        auto min = splaytree.minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test predecessor for a node that does exist") {
        auto predecessor = splaytree.predecessor(9);
        REQUIRE(predecessor != nullptr);
        REQUIRE(predecessor->key == 8);
      }
      THEN("Test successor for a node that does exist") {
        auto successor = splaytree.successor(3);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->key == 4);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = splaytree.predecessor(1917);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = splaytree.successor(1920);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = splaytree.search(1337);
        REQUIRE(result == nullptr);
      }
      THEN("Test search for a node that does exist") {
        auto result = splaytree.search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Call pre_order_traversal") {
        splaytree.pre_order_traversal([](auto key, auto value) {});
      }
      THEN("Call in_order_traversal") {
        splaytree.in_order_traversal([](auto key, auto value) {});
      }
      THEN("Call post_order_traversal") {
        splaytree.post_order_traversal([](auto key, auto value) {});
      }
    }
    WHEN("Nodes are inserted in descending order") {
      for (int i = 9; i >= 0; i--) {
        splaytree.insert(i, 0);
      }
      THEN("Test root") {
        auto root = splaytree.root();
        REQUIRE(root != nullptr);
        REQUIRE(root->key == 0);
      }
      THEN("Test empty") {
        REQUIRE(splaytree.empty() == false);
      }
      THEN("Test size") {
        REQUIRE(splaytree.size() == 10);
      }
      THEN("Test height") {
        REQUIRE(splaytree.height() == 10);
      }
      THEN("Test maximum") {
        auto max = splaytree.maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 9);
      }
      THEN("Test minimum") {
        auto min = splaytree.minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test predecessor for a node that does exist") {
        auto predecessor = splaytree.predecessor(9);
        REQUIRE(predecessor != nullptr);
        REQUIRE(predecessor->key == 8);
      }
      THEN("Test successor for a node that does exist") {
        auto successor = splaytree.successor(3);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->key == 4);
      }
      THEN("Test predecessor for a node that does not exist") {
        auto predecessor = splaytree.predecessor(1917);
        REQUIRE(predecessor == nullptr);
      }
      THEN("Test successor for a node that does not exist") {
        auto successor = splaytree.successor(1920);
        REQUIRE(successor == nullptr);
      }
      THEN("Test search for a node that does not exist") {
        auto result = splaytree.search(1337);
        REQUIRE(result == nullptr);
      }
      THEN("Test search for a node that does exist") {
        auto result = splaytree.search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Call pre_order_traversal") {
        splaytree.pre_order_traversal([](auto key, auto value) {});
      }
      THEN("Call in_order_traversal") {
        splaytree.in_order_traversal([](auto key, auto value) {});
      }
      THEN("Call post_order_traversal") {
        splaytree.post_order_traversal([](auto key, auto value) {});
      }
    }
  }
}
