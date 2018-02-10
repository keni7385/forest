#include <catch.hpp>
#include <forest/trie.h>

SCENARIO("Test Trie") {
        GIVEN("A Trie") {
                forest::trie trie;
                WHEN("The Trie is empty") {
                        THEN("Test search for a key that does not exist") {
                                REQUIRE(trie.search("lol") == false);
                        }
                }
                WHEN("The Trie is not empty") {
			trie.insert("a");
			trie.insert("to");
			trie.insert("tea");
			trie.insert("ted");
			trie.insert("ten");
			trie.insert("i");
			trie.insert("in");
			trie.insert("inn");
			THEN("Test search for some keys that do exist") {
				REQUIRE(trie.search("a") == true);
				REQUIRE(trie.search("to") == true);
				REQUIRE(trie.search("tea") == true);
				REQUIRE(trie.search("ted") == true);
				REQUIRE(trie.search("ten") == true);
				REQUIRE(trie.search("i") == true);
				REQUIRE(trie.search("in") == true);
				REQUIRE(trie.search("inn") == true);
			}
			THEN("Test search for some keys that do not exist") {	
				REQUIRE(trie.search("god") == false);
				REQUIRE(trie.search("too") == false);
			}
		}
	}
}
