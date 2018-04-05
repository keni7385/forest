#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <memory>

namespace forest {
	template <typename T, typename U>
	class red_black_tree {
	private:
		enum Color { red, black };
		struct Node {
			T key;
			U value;
			Color color;
			std::weak_ptr<Node> parent;
			std::shared_ptr<Node> left;
			std::shared_ptr<Node> right;
			Node(T key, U value, Color color) {
				this->key = key;
				this->value = value;
				this->color = color;
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
		void left_rotate(std::shared_ptr<Node> & x) {
			std::shared_ptr<Node> y = x->right;
			if (y != nullptr) {
				x->right = y->left;
				if (y->left != nullptr) y->left->parent = x;
				y->parent = x->parent;
			}
			if (x->parent.lock() == nullptr) {
				root = y;
			}
			else if (x == x->parent.lock()->left) {
				x->parent.lock()->left = y;
			}
			else {
				x->parent.lock()->right = y;
			}
			if (y != nullptr) {
				y->left = x;
			}
			x->parent = y;
		}
		void right_rotate(std::shared_ptr<Node> & x) {
			std::shared_ptr<Node> y = x->left;
			if (y != nullptr) {
				x->left = y->right;
				if (y->right != nullptr) y->right->parent = x;
				y->parent = x->parent;
			}
			if (x->parent.lock() == nullptr) {
				root = y;
			}
			else if (x == x->parent.lock()->left) {
				x->parent.lock()->left = y;
			}
			else {
				x->parent.lock()->right = y;
			}
			if (y != nullptr) {
				y->right = x;
			}
			x->parent = y;
		}
		std::shared_ptr<Node> find_sibling(std::shared_ptr<Node> & x) {
			if (x == find_parent(x)->left) {
				return find_parent(x)->right;
			}
			else if (x == find_parent(x)->right) {
				return find_parent(x)->left;
			}
			return nullptr;
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
		std::shared_ptr<Node> find_uncle(std::shared_ptr<Node> & x) {
			if (find_grand_parent(x) != nullptr) {
				return find_sibling(find_parent(x));
			}
			return nullptr;
		}
		void fix(std::shared_ptr<Node> & x) {
			std::shared_ptr<Node> parent = nullptr;
			std::shared_ptr<Node> grand_parent = nullptr;
			while ((x != root) && (x->color != black) && (x->parent.lock()->color == red)) {
				parent = x->parent.lock();
				grand_parent = x->parent.lock()->parent.lock();
				/**
				* @brief Case A - Parent of x is left child of the grand parent of x
				*/
				if (parent == grand_parent->left) {
					std::shared_ptr<Node> uncle = grand_parent->right;
					/**
					* @brief Case 1 - The uncle of x is also red. Only recoloring is required
					*/
					if (uncle != nullptr && uncle->color == red) {
						grand_parent->color = red;
						parent->color = black;
						uncle->color = black;
						x = grand_parent;
					}
					else {
						/**
						* @brief Case 2 - x is right child of its parent. Left rotation is required
						*/
						if (x == parent->right) {
							left_rotate(parent);
							x = parent;
							parent = x->parent.lock();
						}
						/**
						* @brief Case 3 - x is left child of its parent. Right rotation is required
						*/
						right_rotate(grand_parent);
						std::swap(parent->color, grand_parent->color);
						x = parent;
					}
				}
				else {
					/**
					* @brief Case B - Parent of x is right child of the grand parent of x
					*/
					std::shared_ptr<Node> uncle = grand_parent->left;
					/**
					* @brief Case 1 - The uncle of x is also red. Only recoloring required
					*/
					if ((uncle != nullptr) && (uncle->color == red)) {
						grand_parent->color = red;
						parent->color = black;
						uncle->color = black;
						x = grand_parent;
					}
					else {
						/**
						* @brief Case 2 - x is left child of its parent. Right rotation is required
						*/
						if (x == parent->left) {
							right_rotate(parent);
							x = parent;
							parent = x->parent.lock();
						}
						/**
						* @brief Case 3 - x is right child of its parent. Left rotation is required
						*/
						left_rotate(grand_parent);
						std::swap(parent->color, grand_parent->color);
						x = parent;
					}
				}
			}
			root->color = black;
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
		void insert(T key, U value) {
			std::shared_ptr<Node> current = root;
			std::shared_ptr<Node> parent = nullptr;
			while (current != nullptr) {
				parent = current;
				if (key > current->key) {
					current = current->right;
				}
				else if (key < current->key) {
					current = current->left;
				}
			}
			current = std::make_shared<Node>(key, value, red);
			current->parent = parent;
			if (parent == nullptr) {
				root = current;
			}
			else if (current->key > parent->key) {
				parent->right = current;
			}
			else if (current->key < parent->key) {
				parent->left = current;
			}
			fix(current);
		}
		std::shared_ptr<const Node> search(T key) {
			std::shared_ptr<Node> x = root;
			while (x != nullptr) {
				if (key > x->key) {
					x = x->right;
				}
				else if (key < x->key) {
					x = x->left;
				}
				else {
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
		std::shared_ptr<const Node> successor(T key) {
			std::shared_ptr<Node> x = root;
			while (x != nullptr) {
				if (key > x->key) {
					x = x->right;
				}
				else if (key < x->key) {
					x = x->left;
				}
				else {
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
		std::shared_ptr<const Node> predecessor(T key) {
			std::shared_ptr<Node> x = root;
			while (x != nullptr) {
				if (key > x->key) {
					x = x->right;
				}
				else if (key < x->key) {
					x = x->left;
				}
				else {
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
		bool empty() {
			return root == nullptr;
		}
	};
}