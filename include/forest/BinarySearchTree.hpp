/*
	MIT License

	Copyright(c) 2017 George Fotopoulos

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#pragma once

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <memory>
#include <queue>
#include <utility>

namespace forest {
	template <typename Key, typename Value>
	class BinarySearchTree {
	private:
		class BinarySearchTreeNode {
			friend class BinarySearchTree;

		private:
			BinarySearchTreeNode * left{ nullptr };
			BinarySearchTreeNode * right{ nullptr };

		private:
			unsigned height{ 1 };

		public:
			Key key;
			Value value;

		public:
			BinarySearchTreeNode() = default;
			BinarySearchTreeNode(const Key & KEY, const Value & VALUE) : key(KEY), value(VALUE) { }
			BinarySearchTreeNode(const BinarySearchTreeNode &) = delete;
			BinarySearchTreeNode(BinarySearchTreeNode &&) = delete;
			BinarySearchTreeNode & operator=(const BinarySearchTreeNode &) = delete;
			BinarySearchTreeNode & operator=(BinarySearchTreeNode &&) = delete;
			~BinarySearchTreeNode() = default;
		};

	private:
		BinarySearchTreeNode * tree_root{ nullptr };

	private:
		void pre_order_traversal(const BinarySearchTreeNode * root, std::function <void(const Key &, const Value &)> handler) {
			if (!root) return;
			handler(root->key, root->value);
			pre_order_traversal(root->left, handler);
			pre_order_traversal(root->right, handler);
		}
		void in_order_traversal(const BinarySearchTreeNode * root, std::function <void(const Key &, const Value &)> handler) {
			if (!root) return;
			in_order_traversal(root->left, handler);
			handler(root->key, root->value);
			in_order_traversal(root->right, handler);
		}
		void post_order_traversal(const BinarySearchTreeNode * root, std::function <void(const Key &, const Value &)> handler) {
			if (!root) return;
			post_order_traversal(root->left, handler);
			post_order_traversal(root->right, handler);
			handler(root->key, root->value);
		}
		void breadth_first_traversal(const BinarySearchTreeNode * root, std::function <void(const Key &, const Value &)> handler) {
			if (!root) return;
			std::queue <const BinarySearchTreeNode *> queue;
			queue.push(root);
			while (!queue.empty()) {
				BinarySearchTreeNode * current{ queue.front() };
				handler(current->key, current->value);
				queue.pop();
				if (current->left) queue.push(current->left);
				if (current->right) queue.push(current->right);
			}
		}

	private:
		BinarySearchTreeNode * minimum(BinarySearchTreeNode * root) {
			if (root == nullptr) return nullptr;
			while (root->left != nullptr) root = root->left;
			return root;
		}
		BinarySearchTreeNode * maximum(BinarySearchTreeNode * root) {
			if (root == nullptr) return nullptr;
			while (root->right != nullptr) root = root->right;
			return root;
		}

	private:
		unsigned height(const BinarySearchTreeNode * root) {
			if (!root) return 0;
			return root->height;
		}
		unsigned size(const BinarySearchTreeNode * root) {
			if (!root) return 0;
			return size(root->left) + size(root->right) + 1;
		}

	private:
		BinarySearchTreeNode * insert(BinarySearchTreeNode * root, const Key & key, const Value & value) {
			if (!root) return new BinarySearchTreeNode(key, value);
			else if (key < root->key) root->left = insert(root->left, key, value);
			else if (key > root->key) root->right = insert(root->right, key, value);
			root->height = std::max(height(root->left), height(root->right)) + 1;
			return root;
		}
		BinarySearchTreeNode * remove(BinarySearchTreeNode * root, const Key & key) {
			if (!root) return nullptr;
			else if (key < root->key) root->left = remove(root->left, key);
			else if (key > root->key) root->right = remove(root->right, key);
			else {
				if (!root->left && !root->right) {
					delete root;
					root = nullptr;
				}
				else if (!root->left) {
					BinarySearchTreeNode * tmp{ root };
					root = root->right;
					delete tmp;
					tmp = nullptr;
				}
				else if (!root->right) {
					BinarySearchTreeNode * tmp{ root };
					root = root->left;
					delete tmp;
					tmp = nullptr;
				}
				else {
					BinarySearchTreeNode * min{ minimum(root->right) };
					root->key = min->key;
					root->value = min->value;
					root->right = remove(root->right, min->key);
					//BinarySearchTreeNode * max{ maximum(root->left) };
					//root->key = max->key;
					//root->value = max->value;
					//root->left = remove(root->left, max->key);
				}
			}

			if (!root) return nullptr;
			
			root->height = std::max(height(root->left), height(root->right)) + 1;
			
			return root;
		}
		BinarySearchTreeNode * search(BinarySearchTreeNode * root, const Key & key) {
			while (root != nullptr) {
				if (key > root->key) root = root->right;
				else if (key < root->key) root = root->left;
				else return root;
			}
			return nullptr;
		}

	private:
		void clear(BinarySearchTreeNode * root) {
			if (!root) return;
			if (root->left != nullptr) clear(root->left);
			if (root->right != nullptr) clear(root->right);
			delete root;
			root = nullptr;
		}

	public:
		BinarySearchTree() = default;
		explicit BinarySearchTree(std::initializer_list <std::pair <Key, Value> > list) {
			for (auto element : list) {
				insert(element.first, element.second);
			}
		}
		BinarySearchTree(const BinarySearchTree &) = delete;
		BinarySearchTree(BinarySearchTree &&) = delete;
		BinarySearchTree & operator=(const BinarySearchTree &) = delete;
		BinarySearchTree & operator=(BinarySearchTree &&) = delete;
		~BinarySearchTree() {
			clear();
		}

	public:
		void pre_order_traversal(std::function <void(const Key &, const Value &)> handler) {
			pre_order_traversal(tree_root, handler);
		}
		void in_order_traversal(std::function <void(const Key &, const Value &)> handler) {
			in_order_traversal(tree_root, handler);
		}
		void post_order_traversal(std::function <void(const Key &, const Value &)> handler) {
			post_order_traversal(tree_root, handler);
		}
		void breadth_first_traversal(std::function <void(const Key &, const Value &)> handler) {
			breadth_first_traversal(tree_root, handler);
		}

	public:
		BinarySearchTreeNode * minimum() {
			return minimum(tree_root);
		}
		BinarySearchTreeNode * maximum() {
			return maximum(tree_root);
		}

	public:
		unsigned height() {
			return height(tree_root);
		}
		unsigned size() {
			return size(tree_root);
		}

	public:
		void insert(const Key & key, const Value & value) {
			tree_root = insert(tree_root, key, value);
		}
		void remove(const Key & key) noexcept {
			tree_root = remove(tree_root, key);
		}
		BinarySearchTreeNode * search(const Key & key) {
			return search(tree_root, key);
		}

	public:
		void clear() {
			clear(tree_root);
			tree_root = nullptr;
		}
	};
}