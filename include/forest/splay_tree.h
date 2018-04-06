#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>

namespace forest {
	template <typename T, typename U>
	class splay_tree {
	private:
		struct Node {
			T key;
			U value;
			std::weak_ptr<Node> parent;
			std::shared_ptr<Node> left;
			std::shared_ptr<Node> right;
			Node(T key, U value) {
				this->key = key;
				this->value = value;
			}
		};
		std::shared_ptr<Node> root;
		void pre_order_traversal(std::shared_ptr<Node> & x, void handler(const T & key, const U & value)) {
			if (x == nullptr) return;
			handler(x->key, x->value);
			pre_order_traversal(x->left, handler);
			pre_order_traversal(x->right, handler);
		}
		void in_order_traversal(std::shared_ptr<Node> & x, void handler(const T & key, const U & value)) {
			if (x == nullptr) return;
			in_order_traversal(x->left, handler);
			handler(x->key, x->value);
			in_order_traversal(x->right, handler);
		}
		void post_order_traversal(std::shared_ptr<Node> & x, void handler(const T & key, const U & value)) {
			if (x == nullptr) return;
			post_order_traversal(x->left, handler);
			post_order_traversal(x->right, handler);
			handler(x->key, x->value);
		}
		void breadth_first_traversal(std::shared_ptr<Node> & x, void handler(const T & key, const U & value)) {
			std::queue <std::shared_ptr<Node> > queue;
			if (x == nullptr) return;
			queue.push(x);
			while (queue.empty() == false) {
				std::shared_ptr<Node> y = queue.front();
				handler(y->key, y->value);
				queue.pop();
				if (y->left != nullptr) queue.push(y->left);
				if (y->right != nullptr) queue.push(y->right);
			}
		}
		size_t height(std::shared_ptr<Node> & x) {
			if (x == nullptr) return 0;
			return std::max(height(x->left), height(x->right)) + 1;
		}
		size_t size(std::shared_ptr<Node> & x) {
			if (x == nullptr) return 0;
			return size(x->left) + size(x->right) + 1;
		}
		void left_rotate(const std::shared_ptr<Node> & x) {
			std::shared_ptr<Node> y = x->right;
			if (y != nullptr) {
				x->right = y->left;
				if (y->left != nullptr) y->left->parent = x;
				y->parent = x->parent;
			}
			if (x->parent.lock() == nullptr) {
				root = y;
			} else if (x == x->parent.lock()->left) {
				x->parent.lock()->left = y;
			} else {
				x->parent.lock()->right = y;
			}
			if (y != nullptr) {
				y->left = x;
			}
			x->parent = y;
		}
		void right_rotate(const std::shared_ptr<Node> & x) {
			std::shared_ptr<Node> y = x->left;
			if (y != nullptr) {
				x->left = y->right;
				if (y->right != nullptr) y->right->parent = x;
				y->parent = x->parent;
			}
			if (x->parent.lock() == nullptr) {
				root = y;
			} else if (x == x->parent.lock()->left) {
				x->parent.lock()->left = y;
			} else {
				x->parent.lock()->right = y;
			}
			if (y != nullptr) {
				y->right = x;
			}
			x->parent = y;
		}
		std::shared_ptr<Node> find_parent(std::shared_ptr<Node> & x) {
			return x->parent.lock();
		}
		std::shared_ptr<Node> find_grand_parent(std::shared_ptr<Node> & x) {
			if (find_parent(x) != nullptr) {
				return find_parent(x)->parent.lock();
			}
			return nullptr;
		}
		void splay(std::shared_ptr<Node> & x) {
			while (find_parent(x) != nullptr) {
				if (find_grand_parent(x) == nullptr) {
					if (find_parent(x)->left == x) {
						right_rotate(find_parent(x));
					} else if (find_parent(x)->right == x) {
						left_rotate(find_parent(x));
					}
				} else if (find_parent(x)->left == x && find_grand_parent(x)->left == find_parent(x)) {
					right_rotate(find_grand_parent(x));
					right_rotate(find_parent(x));
				} else if (find_parent(x)->right == x && find_grand_parent(x)->right == find_parent(x)) {
					left_rotate(find_grand_parent(x));
					left_rotate(find_parent(x));
				} else if (find_parent(x)->left == x && find_grand_parent(x)->right == find_parent(x)) {
					right_rotate(find_parent(x));
					left_rotate(find_parent(x));
				} else if (find_parent(x)->right == x && find_grand_parent(x)->left == find_parent(x)) {
					left_rotate(find_parent(x));
					right_rotate(find_parent(x));
				}
			}
		}
	public:
		void pre_order_traversal(void handler(const T & key, const U & value)) {
			pre_order_traversal(root, handler);
		}
		void in_order_traversal(void handler(const T & key, const U & value)) {
			in_order_traversal(root, handler);
		}
		void post_order_traversal(void handler(const T & key, const U & value)) {
			post_order_traversal(root, handler);
		}
		void breadth_first_traversal(void handler(const T & key, const U & value)) {
			breadth_first_traversal(root, handler);
		}
		void insert(const T & key, const U & value) {
			std::shared_ptr<Node> current = root;
			std::shared_ptr<Node> parent = nullptr;
			while (current != nullptr) {
				parent = current;
				if (key > current->key) {
					current = current->right;
				} else if (key < current->key) {
					current = current->left;
				}
			}
			current = std::make_shared<Node>(key, value);
			current->parent = parent;
			if (parent == nullptr) {
				root = current;
			} else if (current->key > parent->key) {
				parent->right = current;
			} else if (current->key < parent->key) {
				parent->left = current;
			}
			splay(current);
		}
		std::shared_ptr<const Node> search(const T & key) {
			std::shared_ptr<Node> x = root;
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
		std::shared_ptr<const Node> minimum() {
			std::shared_ptr<Node> x = root;
			if (x == nullptr) return nullptr;
			while (x->left != nullptr) x = x->left;
			return x;
		}
		std::shared_ptr<const Node> maximum() {
			std::shared_ptr<Node> x = root;
			if (x == nullptr) return nullptr;
			while (x->right != nullptr) x = x->right;
			return x;
		}
		std::shared_ptr<const Node> successor(const T & key) {
			std::shared_ptr<Node> x = root;
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
					std::shared_ptr<Node> parent = x->parent.lock();
					while (parent != nullptr && x == parent->right) {
						x = parent;
						parent = parent->parent.lock();
					}
					return parent;
				}
			}
			return nullptr;
		}
		std::shared_ptr<const Node> predecessor(const T & key) {
			std::shared_ptr<Node> x = root;
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
					std::shared_ptr<Node> parent = x->parent.lock();
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