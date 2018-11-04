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
#include <initializer_list>
#include <memory>
#include <queue>
#include <utility>

namespace forest {
	template <typename Key, typename Value>
	class AVLTree {
	private:
		class AVLTreeNode {
			friend class AVLTree;

		private:
			AVLTreeNode * left{ nullptr };
			AVLTreeNode * right{ nullptr };

		private:
			int height{ 1 };

		public:
			Key key;
			Value value;

		public:
			AVLTreeNode() = default;
			AVLTreeNode(const Key & KEY, const Value & VALUE) : key(KEY), value(VALUE) { }
			AVLTreeNode(const AVLTreeNode &) = delete;
			AVLTreeNode(AVLTreeNode &&) = delete;
			AVLTreeNode& operator=(const AVLTreeNode &) = delete;
			AVLTreeNode& operator=(AVLTreeNode &&) = delete;
			~AVLTreeNode() = default;
		};

	private:
		AVLTreeNode * tree_root{ nullptr };

	private:
		void pre_order_traversal(const AVLTreeNode * root, void handler(const Key & key, const Value & value)) noexcept {
			if (!root) return;
			handler(root->key, root->value);
			pre_order_traversal(root->left, handler);
			pre_order_traversal(root->right, handler);
		}
		void in_order_traversal(const AVLTreeNode * root, void handler(const Key & key, const Value & value)) noexcept {
			if (!root) return;
			in_order_traversal(root->left, handler);
			handler(root->key, root->value);
			in_order_traversal(root->right, handler);
		}
		void post_order_traversal(const AVLTreeNode * root, void handler(const Key & key, const Value & value)) noexcept {
			if (!root) return;
			post_order_traversal(root->left, handler);
			post_order_traversal(root->right, handler);
			handler(root->key, root->value);
		}
		void breadth_first_traversal(const AVLTreeNode * root, void handler(const Key & key, const Value & value)) noexcept {
			std::queue <const AVLTreeNode *> queue;
			if (!root) return;
			queue.push(root);
			while (!queue.empty()) {
				AVLTreeNode * current{ queue.front() };
				handler(current->key, current->value);
				queue.pop();
				if (current->left) queue.push(current->left);
				if (current->right) queue.push(current->right);
			}
		}
	
	private:
		AVLTreeNode * minimum(AVLTreeNode * root) noexcept {
			if (!root) return nullptr;
			while (root->left) root = root->left;
			return root;
		}
		AVLTreeNode * maximum(AVLTreeNode * root) noexcept {
			if (!root) return nullptr;
			while (root->right) root = root->right;
			return root;
		}

	private:
		int height(const AVLTreeNode * root) noexcept {
			if (!root) return 0;
			return root->height;
		}
		int balance(const AVLTreeNode * root) noexcept {
			if (!root) return 0;
			return height(root->left) - height(root->right);
		}
		int size(const AVLTreeNode * root) noexcept {
			if (!root) return 0;
			return size(root->left) + size(root->right) + 1;
		}

	private:
		AVLTreeNode * rotate_right(AVLTreeNode * root) noexcept {
			AVLTreeNode * pivot{ root->left };
			AVLTreeNode * orphan{ pivot->right };

			pivot->right = root;
			root->left = orphan;

			root->height = std::max(height(root->left), height(root->right)) + 1;
			pivot->height = std::max(height(pivot->left), height(pivot->right)) + 1;

			return pivot;
		}
		AVLTreeNode * rotate_left(AVLTreeNode * root) noexcept {
			AVLTreeNode * pivot{ root->right };
			AVLTreeNode * orphan{ pivot->left };

			pivot->left = root;
			root->right = orphan;

			root->height = std::max(height(root->left), height(root->right)) + 1;
			pivot->height = std::max(height(pivot->left), height(pivot->right)) + 1;

			return pivot;
		}

	private:
		AVLTreeNode * insert(AVLTreeNode * root, const Key & key, const Value & value) {
			if (root == nullptr) return new AVLTreeNode(key, value);
			if (key < root->key) root->left = insert(root->left, key, value);
			else if (key > root->key) root->right = insert(root->right, key, value);

			root->height = std::max(height(root->left), height(root->right)) + 1;

			if (balance(root) > 1) {
				if (key < root->left->key) {
					return rotate_right(root);
				}
				else if (key > root->left->key)
				{
					root->left = rotate_left(root->left);
					return rotate_right(root);
				}
			}
			else if (balance(root) < -1) {
				if (key > root->right->key) {
					return rotate_left(root);
				}
				else if (key < root->right->key) {
					root->right = rotate_right(root->right);
					return rotate_left(root);
				}
			}

			return root;
		}
		AVLTreeNode * remove(AVLTreeNode * root, const Key & key) {
			if (!root) return nullptr;
			else if (key < root->key) root->left = remove(root->left, key);
			else if (key > root->key) root->right = remove(root->right, key);
			else {
				if (!root->left && !root->right) {
					delete root;
					root = nullptr;
				}
				else if (!root->left) {
					AVLTreeNode * tmp{ root };
					root = root->right;
					delete tmp;
					tmp = nullptr;
				}
				else if (!root->right) {
					AVLTreeNode * tmp{ root };
					root = root->left;
					delete tmp;
					tmp = nullptr;
				}
				else {
					AVLTreeNode * min{ minimum(root->right) };
					root->key = min->key;
					root->value = min->value;
					root->right = remove(root->right, min->key);
					//AVLTreeNode * max{ maximum(root->left) };
					//root->key = max->key;
					//root->value = max->value;
					//root->left = remove(root->left, max->key);
				}
			}

			if (!root) return nullptr;

			root->height = std::max(height(root->left), height(root->right)) + 1;

			if (balance(root) > 1) {
				if (balance(root->left) >= 0) {
					return rotate_right(root);
				}
				else {
					root->left = rotate_left(root->left);
					return rotate_right(root);
				}
			}
			else if (balance(root) < -1) {
				if (balance(root->right) <= 0) {
					return rotate_left(root);
				}
				else {
					root->right = rotate_right(root->right);
					return rotate_left(root);
				}
			}

			return root;
		}
		AVLTreeNode * search(AVLTreeNode * root, const Key & key) noexcept {
			while (root) {
				if (key > root->key) {
					root = root->right;
				}
				else if (key < root->key) {
					root = root->left;
				}
				else {
					return root;
				}
			}
			return nullptr;
		}

	private:
		void clear(AVLTreeNode * root) {
			if (!root) return;
			if (root->left != nullptr) clear(root->left);
			if (root->right != nullptr) clear(root->right);
			delete root;
			root = nullptr;
		}

	public:
		AVLTree() = default;
		explicit AVLTree(std::initializer_list <std::pair <Key, Value> > list) {
			for (auto element : list) {
				insert(element.first, element.second);
			}
		}
		AVLTree(const AVLTree &) = delete;
		AVLTree(AVLTree &&) = delete;
		AVLTree& operator=(const AVLTree &) = delete;
		AVLTree& operator=(AVLTree &&) = delete;
		~AVLTree() {
			clear();
		}

	public:
		void pre_order_traversal(void handler(const Key & key, const Value & value)) noexcept {
			pre_order_traversal(tree_root, handler);
		}
		void in_order_traversal(void handler(const Key & key, const Value & value)) noexcept {
			in_order_traversal(tree_root, handler);
		}
		void post_order_traversal(void handler(const Key & key, const Value & value)) noexcept {
			post_order_traversal(tree_root, handler);
		}
		void breadth_first_traversal(void handler(const Key & key, const Value & value)) noexcept {
			breadth_first_traversal(tree_root, handler);
		}

	public:
		AVLTreeNode * minimum() noexcept {
			return minimum(tree_root);
		}
		AVLTreeNode * maximum() noexcept {
			return maximum(tree_root);
		}

	public:
		int height() noexcept {
			return height(tree_root);
		}
		int size() noexcept {
			return size(tree_root);
		}

	public:
		void insert(const Key & key, const Value & value) noexcept {
			tree_root = insert(tree_root, key, value);
		}
		void remove(const Key & key) {
			tree_root = remove(tree_root, key);
		}
		AVLTreeNode * search(const Key & key) noexcept {
			return search(tree_root, key);
		}

	public:
		void clear() {
			clear(tree_root);
			tree_root = nullptr;
		}
	};
}