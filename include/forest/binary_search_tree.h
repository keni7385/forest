#pragma once

#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>
#include <memory>

namespace forest {
	template <typename T>
	class binary_search_tree {
	private:
		struct node {
			T key;
			std::weak_ptr<node> parent;
			std::shared_ptr<node> left;
			std::shared_ptr<node> right;
			node(const T key) {
				this->key = key;
			}
		};
		std::shared_ptr<node> root;
		void pre_order_traversal(std::shared_ptr<node> & x, void handler(const T & key)) {
			if (x == nullptr) return;
			handler(x->key);
			pre_order_traversal(x->left, handler);
			pre_order_traversal(x->right, handler);
		}
		void in_order_traversal(std::shared_ptr<node> & x, void handler(const T & key)) {
			if (x == nullptr) return;
			in_order_traversal(x->left, handler);
			handler(x->key);
			in_order_traversal(x->right, handler);
		}
		void post_order_traversal(std::shared_ptr<node> & x, void handler(const T & key)) {
			if (x == nullptr) return;
			post_order_traversal(x->left, handler);
			post_order_traversal(x->right, handler);
			handler(x->key);
		}
		void breadth_first_traversal(std::shared_ptr<node> & x, void handler(const T & key)) {
			std::queue <std::shared_ptr<node> > queue;
			if (x == nullptr) return;
			queue.push(x);
			while (queue.empty() == false) {
				std::shared_ptr<node> y = queue.front();
				handler(y->key);
				queue.pop();
				if (y->left != nullptr) queue.push(y->left);
				if (y->right != nullptr) queue.push(y->right);
			}
		}
		size_t height(std::shared_ptr<node> & x) {
			if (x == nullptr) return 0;
			return std::max(height(x->left), height(x->right)) + 1;
		}
		size_t size(std::shared_ptr<node> & x) {
			if (x == nullptr) return 0;
			return size(x->left) + size(x->right) + 1;
		}
	public:
		void pre_order_traversal(void handler(const T & key)) {
			pre_order_traversal(root, handler);
		}
		void in_order_traversal(void handler(const T & key)) {
			in_order_traversal(root, handler);
		}
		void post_order_traversal(void handler(const T & key)) {
			post_order_traversal(root, handler);
		}
		void breadth_first_traversal(void handler(const T & key)) {
			breadth_first_traversal(root, handler);
		}
		std::shared_ptr<const node> insert(const T & key) {
			std::shared_ptr<node> current = root;
			std::shared_ptr<node> parent = nullptr;
			while (current != nullptr) {
				parent = current;
				if (key > current->key) {
					current = current->right;
				} else if (key < current->key) {
					current = current->left;
				} else {
					return nullptr;
				}
			}
			current = std::make_shared<node>(key);
			current->parent = parent;
			if (parent == nullptr) {
				root = current;
			} else if (current->key > parent->key) {
				parent->right = current;
			} else if (current->key < parent->key) {
				parent->left = current;
			}
			return current;
		}
		std::shared_ptr<const node> search(const T & key) {
			std::shared_ptr<node> x = root;
			while (x != nullptr) {
				if (key > x->key) {
					x = x->right;
				} else if (key < x->key) {
					x = x->left;
				} else {
					return x;
				}
			}
			return nullptr;
		}
		std::shared_ptr<const node> minimum() {
			std::shared_ptr<node> x = root;
			if (x == nullptr) return nullptr;
			while (x->left != nullptr) x = x->left;
			return x;
		}
		std::shared_ptr<const node> maximum() {
			std::shared_ptr<node> x = root;
			if (x == nullptr) return nullptr;
			while (x->right != nullptr) x = x->right;
			return x;
		}
		std::shared_ptr<const node> successor(const T & key) {
			std::shared_ptr<node> x = root;
			while (x != nullptr) {
				if (key > x->key) {
					x = x->right;
				} else if (key < x->key) {
					x = x->left;
				} else {
					if (x->right != nullptr) {
						x = x->right;
						while (x->left != nullptr) x = x->left;
						return x;
					}
					std::shared_ptr<node> parent = x->parent.lock();
					while (parent != nullptr && x == parent->right) {
						x = parent;
						parent = parent->parent.lock();
					}
					return parent;
				}
			}
			return nullptr;
		}
		std::shared_ptr<const node> predecessor(const T & key) {
			std::shared_ptr<node> x = root;
			while (x != nullptr) {
				if (key > x->key) {
					x = x->right;
				} else if (key < x->key) {
					x = x->left;
				} else {
					if (x->left != nullptr) {
						x = x->left;
						while (x->right != nullptr) x = x->right;
						return x;
					}
					std::shared_ptr<node> parent = x->parent.lock();
					while (parent != nullptr && x == parent->left) {
						x = parent;
						parent = parent->parent.lock();
					}
					return parent;
				}
			}
			return nullptr;
		}
		size_t height() {
			return height(root);
		}
		size_t size() {
			return size(root);
		}
		bool empty() const {
			return (root == nullptr);
		}
	};
}