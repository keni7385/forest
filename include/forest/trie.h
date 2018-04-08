#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace forest {
	class trie {
	private:
		static constexpr size_t alphabet_size = 1 + 'z' - 'a';
		int char_to_int(char c) {
			return c - 'a';
		}
		bool validate(std::string key) {
			size_t index;
			for (auto c : key) {
				try {
					index = char_to_int(c);
					if (index < 0 || index >= alphabet_size) {
						throw std::invalid_argument("[forest::trie] unsupported character found");
					}
				}
				catch (std::invalid_argument e) {
					return false;
				}
			}
			return true;
		}
		struct Node {
			std::unique_ptr<Node> children[alphabet_size];
			bool end = false;
		};
		std::unique_ptr<Node> root = std::make_unique<Node>();
	public:
		bool insert(const std::string & key) {
			if (!validate(key)) return false;
			Node * n = root.get();
			for (auto c : key) {
				size_t index = char_to_int(c);
				auto& slot = n->children[index];
				if (!slot) slot = std::make_unique<Node>();
				n = slot.get();
			}
			n->end = true;
			return true;
		}
		bool search(const std::string & key) {
			if (!validate(key)) return false;
			Node * n = root.get();
			for (auto c : key) {
				size_t index = char_to_int(c);
				auto& slot = n->children[index];
				if (!slot) return false;
				n = slot.get();
			}
			return n->end;
		}
	};
}