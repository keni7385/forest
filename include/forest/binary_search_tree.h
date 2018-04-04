/**
* @file binary_search_tree.h
*/

#pragma once

#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>
#include <memory>

/**
* @brief The forest library namespace
*/
namespace forest {
	template <typename T>
	class binary_search_tree {
	private:
		struct node {
			T key;                         ///< The key of the node
			std::weak_ptr<node> parent;    ///< The parent of the node
			std::shared_ptr<node> left;    ///< The left child of the node
			std::shared_ptr<node> right;   ///< The right child of the node
			node(const T key) {
				this->key = key;
				this->parent.reset();
				this->left = nullptr;
				this->right = nullptr;
			}
		};
		std::shared_ptr<node> root;
		void pre_order_traversal(std::shared_ptr<node> &x, void handler(const T & key)) {
			if (x == nullptr) return;
			handler(x->key);
			pre_order_traversal(x->left, handler);
			pre_order_traversal(x->right, handler);
		}
		void in_order_traversal(std::shared_ptr<node> &x, void handler(const T & key)) {
			if (x == nullptr) return;
			in_order_traversal(x->left, handler);
			handler(x->key);
			in_order_traversal(x->right, handler);
		}
		void post_order_traversal(std::shared_ptr<node> &x, void handler(const T & key)) {
			if (x == nullptr) return;
			post_order_traversal(x->left, handler);
			post_order_traversal(x->right, handler);
			handler(x->key);
		}
		void breadth_first_traversal(std::shared_ptr<node> &x, void handler(const T & key)) {
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
		const unsigned long long height(std::shared_ptr<node> &x) {
			if (x == nullptr) return 0;
			return std::max(height(x->left), height(x->right)) + 1;
		}
		const unsigned long long size(std::shared_ptr<node> &x) {
			if (x == nullptr) return 0;
			return size(x->left) + size(x->right) + 1;
		}
	public:
		/**
		* @brief Performs a Pre Order Traversal starting from the root node
		* @return void
		*/
		void pre_order_traversal(void handler(const T & key)) {
			pre_order_traversal(root, handler);
		}
		/**
		* @brief Performs a In Order Traversal starting from the root node
		* @return void
		*/
		void in_order_traversal(void handler(const T & key)) {
			in_order_traversal(root, handler);
		}
		/**
		* @brief Performs a Post Order Traversal starting from the root node
		* @return void
		*/
		void post_order_traversal(void handler(const T & key)) {
			post_order_traversal(root, handler);
		}
		/**
		* @brief Performs a Breadth First Traversal starting from the root node
		* @return void
		*/
		void breadth_first_traversal(void handler(const T & key)) {
			breadth_first_traversal(root, handler);
		}
		/**
		* @brief Inserts a new node into the binary search tree
		* @param key The key for the new node
		* @return The the inserted node otherwise nullptr
		*/
		const std::shared_ptr<node> insert(const T key) {
			std::shared_ptr<node> current = root;
			std::shared_ptr<node> parent = nullptr;
			while (current != nullptr) {
				parent = current;
				if (key > current->key) {
					current = current->right;
				}
				else if (key < current->key) {
					current = current->left;
				}
				else {
					return nullptr;
				}
			}
			current = std::make_shared<node>(key);
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
			return current;
		}
		/**
		* @brief Performs a binary search starting from the root node
		* @return The node with the key specified otherwise nullptr
		*/
		const std::shared_ptr<node> search(const T key) {
			std::shared_ptr<node> x = root;
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
		/**
		* @brief Finds the node with the minimum key
		* @return The node with the minimum key otherwise nullptr
		*/
		const std::shared_ptr<node> minimum() {
			std::shared_ptr<node> x = root;
			if (x == nullptr) return nullptr;
			while (x->left != nullptr) x = x->left;
			return x;
		}
		/**
		* @brief Finds the node with the maximum key
		* @return The node with the maximum key otherwise nullptr
		*/
		const std::shared_ptr<node> maximum() {
			std::shared_ptr<node> x = root;
			if (x == nullptr) return nullptr;
			while (x->right != nullptr) x = x->right;
			return x;
		}
		/**
		* @brief Finds the successor of the node with key specified
		* @return The successor of the node with key specified otherwise nullptr
		*/
		const std::shared_ptr<node> successor(const T key) {
			std::shared_ptr<node> x = root;
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
		/**
		* @brief Finds the predecessor of the node with key specified
		* @return The predecessor of the node with key specified otherwise nullptr
		*/
		const std::shared_ptr<node> predecessor(const T key) {
			std::shared_ptr<node> x = root;
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
		/**
		* @brief Finds the height of the binary search tree
		* @return The height of the binary search tree
		*/
		const unsigned long long height() {
			return height(root);
		}
		/**
		* @brief Finds the size of the binary search tree
		* @return The size of the binary search tree
		*/
		const unsigned long long size() {
			return size(root);
		}
		/**
		* @brief Finds if the binary search tree is empty
		* @return true if the binary search tree is empty and false otherwise
		*/
		const bool empty() const {
			return (root == nullptr);
		}
	};
}