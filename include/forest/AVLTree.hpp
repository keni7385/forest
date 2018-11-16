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
#include <queue>
#include <utility>

namespace forest {
	template <typename Key, typename Value>
	class AVLTree {
	public:
		using Pair = std::pair <Key, Value>;
		using Pairs = std::initializer_list<Pair>;
		using Handler = std::function <void(const Key &, const Value &)>;

	private:
		class AVLTreeNode {
			friend class AVLTree;

		private:
			AVLTreeNode * left{ nullptr };
			AVLTreeNode * right{ nullptr };

		private:
			unsigned height{ 1 };

		public:
			Key key;
			Value value;

		public:
			AVLTreeNode() = default;
			AVLTreeNode(const Key & KEY, const Value & VALUE) : key(KEY), value(VALUE) { }
			AVLTreeNode(const AVLTreeNode &) = delete;
			AVLTreeNode(AVLTreeNode &&) = delete;
			AVLTreeNode & operator=(const AVLTreeNode &) = delete;
			AVLTreeNode & operator=(AVLTreeNode &&) = delete;
			~AVLTreeNode() = default;
		};

	private:
		AVLTreeNode * tree_root{ nullptr };

	private:
		void pre_order_traversal(const AVLTreeNode * root, Handler handler) {
			if (!root) return;
			handler(root->key, root->value);
			pre_order_traversal(root->left, handler);
			pre_order_traversal(root->right, handler);
		}
		void in_order_traversal(const AVLTreeNode * root, Handler handler) {
			if (!root) return;
			in_order_traversal(root->left, handler);
			handler(root->key, root->value);
			in_order_traversal(root->right, handler);
		}
		void post_order_traversal(const AVLTreeNode * root, Handler handler) {
			if (!root) return;
			post_order_traversal(root->left, handler);
			post_order_traversal(root->right, handler);
			handler(root->key, root->value);
		}
		void breadth_first_traversal(const AVLTreeNode * root, Handler handler) {
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
		AVLTreeNode * minimum(AVLTreeNode * root) {
			if (!root) return nullptr;
			while (root->left) root = root->left;
			return root;
		}
		AVLTreeNode * maximum(AVLTreeNode * root) {
			if (!root) return nullptr;
			while (root->right) root = root->right;
			return root;
		}

	private:
		int balance(const AVLTreeNode * root) {
			if (!root) return 0;
			return height(root->left) - height(root->right);
		}

	private:
		unsigned height(const AVLTreeNode * root) {
			if (!root) return 0;
			return root->height;
		}
		unsigned size(const AVLTreeNode * root) {
			if (!root) return 0;
			return size(root->left) + size(root->right) + 1;
		}

	private:
		AVLTreeNode * rotate_right(AVLTreeNode * root) {
			AVLTreeNode * pivot{ root->left };
			AVLTreeNode * orphan{ pivot->right };

			pivot->right = root;
			root->left = orphan;

			root->height = std::max(height(root->left), height(root->right)) + 1;
			pivot->height = std::max(height(pivot->left), height(pivot->right)) + 1;

			return pivot;
		}
		AVLTreeNode * rotate_left(AVLTreeNode * root) {
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
			if (!root) return new AVLTreeNode(key, value);
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
		AVLTreeNode * search(AVLTreeNode * root, const Key & key) {
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
			if (root->left) clear(root->left);
			if (root->right) clear(root->right);
			delete root;
			root = nullptr;
		}

	public:
		AVLTree() = default;
		explicit AVLTree(Pairs pairs) {
			for (auto pair : pairs) {
				insert(pair.first, pair.second);
			}
		}
		AVLTree(const AVLTree &) = delete;
		AVLTree(AVLTree &&) = delete;
		AVLTree & operator=(const AVLTree &) = delete;
		AVLTree & operator=(AVLTree &&) = delete;
		~AVLTree() {
			clear();
		}

	public:
		void pre_order_traversal(Handler handler) {
			pre_order_traversal(tree_root, handler);
		}
		void in_order_traversal(Handler handler) {
			in_order_traversal(tree_root, handler);
		}
		void post_order_traversal(Handler handler) {
			post_order_traversal(tree_root, handler);
		}
		void breadth_first_traversal(Handler handler) {
			breadth_first_traversal(tree_root, handler);
		}

	public:
		AVLTreeNode * minimum() {
			return minimum(tree_root);
		}
		AVLTreeNode * maximum() {
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
		void remove(const Key & key) {
			tree_root = remove(tree_root, key);
		}
		AVLTreeNode * search(const Key & key) {
			return search(tree_root, key);
		}

	public:
		void clear() {
			clear(tree_root);
			tree_root = nullptr;
		}
	};
}