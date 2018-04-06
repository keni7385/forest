#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace forest {
	class trie {
	private:
		struct Node {
			std::shared_ptr<Node> children[26];
			bool end = false;
		};
		std::shared_ptr<Node> root = std::make_shared<Node>();
	public:
		void insert(const std::string & key) {
			std::shared_ptr<Node> n = root;
			for (auto c : key) {
				int index = c - 'a';
				auto& slot = n->children[index];
				if (!slot) slot = std::make_shared<Node>();
				n = slot;
			}
			n->end = true;
		}
		bool search(const std::string & key) {
			std::shared_ptr<Node> n = root;
			for (auto c : key) {
				int index = c - 'a';
				auto& slot = n->children[index];
				if (!slot) return false;
				n = slot;
			}
			return n && n->end;
		}
	};
}