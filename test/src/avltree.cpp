#include <catch.hpp>
#include <forest/avltree.hpp>

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
        avltree.pre_order_traversal([](auto key, auto value) {});
      }
      THEN("Call in_order_traversal") {
        avltree.in_order_traversal([](auto key, auto value) {});
      }
      THEN("Call post_order_traversal") {
        avltree.post_order_traversal([](auto key, auto value) {});
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
        avltree.pre_order_traversal([](auto key, auto value) {});
      }
      THEN("Call in_order_traversal") {
        avltree.in_order_traversal([](auto key, auto value) {});
      }
      THEN("Call post_order_traversal") {
        avltree.post_order_traversal([](auto key, auto value) {});
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
        avltree.pre_order_traversal([](auto key, auto value) {});
      }
      THEN("Call in_order_traversal") {
        avltree.in_order_traversal([](auto key, auto value) {});
      }
      THEN("Call post_order_traversal") {
        avltree.post_order_traversal([](auto key, auto value) {});
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
        avltree.pre_order_traversal([](auto key, auto value) {});
      }
      THEN("Call in_order_traversal") {
        avltree.in_order_traversal([](auto key, auto value) {});
      }
      THEN("Call post_order_traversal") {
        avltree.post_order_traversal([](auto key, auto value) {});
      }
    }
  }
}
