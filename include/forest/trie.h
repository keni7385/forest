/**
* @file trie.h
*/

#ifndef FOREST_TRIE_H
#define FOREST_TRIE_H

#include <iostream>
#include <string>
#include <memory>

namespace forest {
	class Trie {
	private:
		#define ALPHABET_SIZE 26
		struct Node {
			std::shared_ptr<Node> children[ALPHABET_SIZE];
			bool end;
			Node() {
				this->end = false;
				for (int i = 0; i < ALPHABET_SIZE; i++) {
					this->children[i] = NULL;
				}
			}
		};
		std::shared_ptr<Node> root;
	public:
		Trie() {
			root = std::make_shared<Node>();
		}
		void insert(const std::string &key) {
			std::shared_ptr<Node> n = root;
			for (int i = 0; i < key.length(); i++) {
				int index = key[i] - 'a';
				if (n->children[index] == nullptr) {
					n->children[index] = std::make_shared<Node>();
				}
				n = n->children[index];
			}
			n->end = true;
		}
		const bool search(const std::string &key) {
			std::shared_ptr<Node> n = root;
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