#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace forest {
	class trie {
	private:
		static constexpr size_t alphabet_size = 26;
		size_t to_index(char c) {
			return c - 'a';
		}
		bool validate(const std::string & key) {
			size_t index;
			for (auto c : key) {
					index = to_index(c);
					if (index < 0 || index >= alphabet_size) {
						return false;
					}
			}
			return true;
		}
		struct Node {
			std::unique_ptr<Node> children[alphabet_size];
			bool end = false;
		};
		std::unique_ptr<Node> root_ = std::make_unique<Node>();
	public:
		bool insert(const std::string & key) {
			if (!validate(key)) return false;
			Node * n = root_.get();
			for (auto c : key) {
				size_t index = to_index(c);
				auto& slot = n->children[index];
				if (!slot) slot = std::make_unique<Node>();
				n = slot.get();
			}
			n->end = true;
			return true;
		}
		bool search(const std::string & key) {
			if (!validate(key)) return false;
			Node * n = root_.get();
			for (auto c : key) {
				size_t index = to_index(c);
				auto& slot = n->children[index];
				if (!slot) return false;
				n = slot.get();
			}
			return n->end;
		}
	};
}