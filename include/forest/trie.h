/**
 * @file trie.h
 */

#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <memory>

#define ALPHABET_SIZE 26

/**
 * @brief The forest library namespace
 */
namespace forest {
	/**
	 * @brief Trie node struct
	 */
	struct trie_node {
		trie_node() {
			this->end = false; 
			for (int i = 0; i < ALPHABET_SIZE; i++) {
				this->children[i] = NULL;
			}
		}
		std::shared_ptr<trie_node> children[ALPHABET_SIZE];
		bool end;
	};
	/**
	 * @brief Trie class
	 */
	class trie {
	private:
		std::shared_ptr<trie_node> root;
	public:
		trie() {
			root = std::make_shared<trie_node>();
		}
		/**
		 * @brief Inserts the given key into the Trie
		 * @param key The key to be inserted
		 * @return void
		 */		
		void insert(std::string key) {
			std::shared_ptr<trie_node> n = root;
			for (int i = 0; i < key.length(); i++) {
				int index = key[i] - 'a';
				if (n->children[index] == nullptr) {
					n->children[index] = std::make_shared<trie_node>();
				}
				n = n->children[index];
			}
			n->end = true;
		}
		/**
		 * @brief Searches for the given key in the Trie
		 * @param key The key to be inserted
		 * @return true if key exists in the Trie and false otherwise
		 */
		bool search(std::string key) {
			std::shared_ptr<trie_node> n = root;
			for (int i = 0; i < key.length(); i++) {
				int index = key[i] - 'a';
				if (n->children[index] == nullptr) {
					return false;
				}
				n = n->children[index];
			}
			return (n != nullptr && n->end == true);
		}
	};
}

#endif
