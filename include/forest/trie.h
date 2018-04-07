#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace forest {
	class trie {
	private:
    static constexpr size_t alphabet_size = 1 + 'z' - 'a';
		int char_to_int(char c) {
      int index = c - 'a';
      if (index <0 || index >= alphabet_size) throw std::invalid_argument("oops");
    }
		struct Node {
			std::shared_ptr<Node> children[alphabet_size];
			bool end = false;
		};
		std::shared_ptr<Node> root = std::make_shared<Node>();
	public:
		void insert(const std::string & key) {
			Node * n = root.get();
			for (auto c : key) {
				int index = char_to_int(c);
				auto& slot = n->children[index];
				if (!slot) slot = std::make_shared<Node>();
				n = slot.get();
			}
			n->end = true;
		}
		bool search(const std::string & key) {
			Node * n = root.get();
			for (auto c : key) {
				int index = char_to_int(c);
				auto& slot = n->children[index];
				if (!slot) return false;
				n = slot.get();
			}
			return n->end;
		}
	};
}