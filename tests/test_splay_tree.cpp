#include "catch.hpp"
#include <forest/splay_tree.h>

SCENARIO("Test Splay Tree") {
        GIVEN("A Splay Tree") {
                forest::splay_tree <int, int> splay_tree;
                WHEN("The Splay Tree is empty") {
                        THEN("Test empty") {
                                REQUIRE(splay_tree.empty() == true);
                        }
                        THEN("Test size") {
                                REQUIRE(splay_tree.size() == 0);
                        }
                        THEN("Test height") {
                                REQUIRE(splay_tree.height() == 0);
                        }
                        THEN("Test maximum") {
                                auto max = splay_tree.maximum();
                                REQUIRE(max == nullptr);
                        }
                        THEN("Test minimum") {
                                auto min = splay_tree.minimum();
                                REQUIRE(min == nullptr);
                        }
                        THEN("Test predecessor for a node that does not exist") {
                                auto predecessor = splay_tree.predecessor(1911);
                                REQUIRE(predecessor == nullptr);
                        }
                        THEN("Test successor for a node that does not exist") {
                                auto successor = splay_tree.successor(1337);
                                REQUIRE(successor == nullptr);
                        }
                        THEN("Test search for a node that does not exist") {
                                auto result = splay_tree.search(555);
                                REQUIRE(result == nullptr);
                        }
                }
                WHEN("Nodes are inserted in random order") {
                        REQUIRE(splay_tree.insert(4 , -10) != nullptr);
                        REQUIRE(splay_tree.insert(2 ,  30) != nullptr);
                        REQUIRE(splay_tree.insert(90, -74) != nullptr);
                        REQUIRE(splay_tree.insert(3 ,   1) != nullptr);
                        REQUIRE(splay_tree.insert(0 ,-110) != nullptr);
                        REQUIRE(splay_tree.insert(14,   0) != nullptr);
                        REQUIRE(splay_tree.insert(45,   0) != nullptr);
                        THEN("Test empty") {
                                REQUIRE(splay_tree.empty() == false);
                        }
                        THEN("Test size") {
                                REQUIRE(splay_tree.size() == 7);
                        }
                        THEN("Test height") {
                                REQUIRE(splay_tree.height() == 5);
                        }
                        THEN("Test maximum") {
                                auto max = splay_tree.maximum();
                                REQUIRE(max != nullptr);
                                REQUIRE(max->key == 90);
                                REQUIRE(max->value == -74);
                        }
                        THEN("Test minimum") {
                                auto min = splay_tree.minimum();
                                REQUIRE(min != nullptr);
                                REQUIRE(min->key == 0);
                                REQUIRE(min->value == -110);
                        }
                        THEN("Test predecessor for a node that does exist") {
                                auto predecessor = splay_tree.predecessor(90);
                                REQUIRE(predecessor != nullptr);
                                REQUIRE(predecessor->key == 45);
                        }
                        THEN("Test successor for a node that does exist") {
                                auto successor = splay_tree.successor(0);
                                REQUIRE(successor != nullptr);
                                REQUIRE(successor->key == 2);
                        }
                        THEN("Test predecessor for a node that does not exist") {
                                auto predecessor = splay_tree.predecessor(1917);
                                REQUIRE(predecessor == nullptr);
                        }
                        THEN("Test successor for a node that does not exist") {
                                auto successor = splay_tree.successor(1920);
                                REQUIRE(successor == nullptr);
                        }
                        THEN("Test search for a node that does not exist") {
                                auto result = splay_tree.search(1337);
                                REQUIRE(result == nullptr);
                        }
                        THEN("Test search for a node that does exist") {
                                auto result = splay_tree.search(3);
                                REQUIRE(result != nullptr);
                                REQUIRE(result->key == 3);
                                REQUIRE(result->value == 1);
                        }
                }
                WHEN("Nodes are inserted in ascending order") {
                        for (int i = 0; i < 10; i++) {
                                REQUIRE(splay_tree.insert(i, i*i) != nullptr);
                        }
                        THEN("Test empty") {
                                REQUIRE(splay_tree.empty() == false);
                        }
                        THEN("Test size") {
                                REQUIRE(splay_tree.size() == 10);
                        }
                        THEN("Test height") {
                                REQUIRE(splay_tree.height() == 10);
                        }
                        THEN("Test maximum") {
                                auto max = splay_tree.maximum();
                                REQUIRE(max != nullptr);
                                REQUIRE(max->key == 9);
                                REQUIRE(max->value == 81);
                        }
                        THEN("Test minimum") {
                                auto min = splay_tree.minimum();
                                REQUIRE(min != nullptr);
                                REQUIRE(min->key == 0);
                                REQUIRE(min->value == 0);
                        }
                        THEN("Test predecessor for a node that does exist") {
                                auto predecessor = splay_tree.predecessor(9);
                                REQUIRE(predecessor != nullptr);
                                REQUIRE(predecessor->key == 8);
                        }
                        THEN("Test successor for a node that does exist") {
                                auto successor = splay_tree.successor(3);
                                REQUIRE(successor != nullptr);
                                REQUIRE(successor->key == 4);
                        }
                        THEN("Test predecessor for a node that does not exist") {
                                auto predecessor = splay_tree.predecessor(1917);
                                REQUIRE(predecessor == nullptr);
                        }
                        THEN("Test successor for a node that does not exist") {
                                auto successor = splay_tree.successor(1920);
                                REQUIRE(successor == nullptr);
                        }
                        THEN("Test search for a node that does not exist") {
                                auto result = splay_tree.search(1337);
                                REQUIRE(result == nullptr);
                        }
                        THEN("Test search for a node that does exist") {
                                auto result = splay_tree.search(3);
                                REQUIRE(result != nullptr);
                                REQUIRE(result->key == 3);
                                REQUIRE(result->value == 9);
                        }
                }
                WHEN("Nodes are inserted in descending order") {
                        for (int i = 9; i >= 0; i--) {
                                REQUIRE(splay_tree.insert(i, i*i) != nullptr);
                        }
                        THEN("Test empty") {
                                REQUIRE(splay_tree.empty() == false);
                        }
                        THEN("Test size") {
                                REQUIRE(splay_tree.size() == 10);
                        }
                        THEN("Test height") {
                                REQUIRE(splay_tree.height() == 10);
                        }
                        THEN("Test maximum") {
                                auto max = splay_tree.maximum();
                                REQUIRE(max != nullptr);
                                REQUIRE(max->key == 9);
                                REQUIRE(max->value == 81);
                        }
                        THEN("Test minimum") {
                                auto min = splay_tree.minimum();
                                REQUIRE(min != nullptr);
                                REQUIRE(min->key == 0);
                                REQUIRE(min->value == 0);
                        }
                        THEN("Test predecessor for a node that does exist") {
                                auto predecessor = splay_tree.predecessor(9);
                                REQUIRE(predecessor != nullptr);
                                REQUIRE(predecessor->key == 8);
                        }
                        THEN("Test successor for a node that does exist") {
                                auto successor = splay_tree.successor(3);
                                REQUIRE(successor != nullptr);
                                REQUIRE(successor->key == 4);
                        }
                        THEN("Test predecessor for a node that does not exist") {
                                auto predecessor = splay_tree.predecessor(1917);
                                REQUIRE(predecessor == nullptr);
                        }
                        THEN("Test successor for a node that does not exist") {
                                auto successor = splay_tree.successor(1920);
                                REQUIRE(successor == nullptr);
                        }
                        THEN("Test search for a node that does not exist") {
                                auto result = splay_tree.search(1337);
                                REQUIRE(result == nullptr);
                        }
                        THEN("Test search for a node that does exist") {
                                auto result = splay_tree.search(3);
                                REQUIRE(result != nullptr);
                                REQUIRE(result->key == 3);
                                REQUIRE(result->value == 9);
                        }
                }
        }
}
