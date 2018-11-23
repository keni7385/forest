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
	class SplayTree {
	public:
		using Keys = std::vector<Key>;
		using Values = std::vector<Value>;
		using Pair = std::pair<Key, Value>;
		using Pairs = std::initializer_list<Pair>;
		using Handler = std::function<void(const Key &, Value &)>;

	private:
		class SplayTreeNode {
			friend class SplayTree;

		private:
			SplayTreeNode * parent{ nullptr };
			SplayTreeNode * left{ nullptr };
			SplayTreeNode * right{ nullptr };

		public:
			Key key;
			Value value;

		public:
			SplayTreeNode() = default;
			SplayTreeNode(const Key & KEY, const Value & VALUE) : key(KEY), value(VALUE) { }
			SplayTreeNode(const SplayTreeNode &) = delete;
			SplayTreeNode(SplayTreeNode &&) = delete;
			~SplayTreeNode() = default;

		public:
			SplayTreeNode & operator=(const SplayTreeNode &) = delete;
			SplayTreeNode & operator=(SplayTreeNode &&) = delete;
		};

	private:
		SplayTreeNode * tree_root{ nullptr };

	private:
		void pre_order_traversal(SplayTreeNode * root, Handler handler) {
			if (!root) return;
			handler(root->key, root->value);
			pre_order_traversal(root->left, handler);
			pre_order_traversal(root->right, handler);
		}
		void in_order_traversal(SplayTreeNode * root, Handler handler) {
			if (!root) return;
			in_order_traversal(root->left, handler);
			handler(root->key, root->value);
			in_order_traversal(root->right, handler);
		}
		void post_order_traversal(SplayTreeNode * root, Handler handler) {
			if (!root) return;
			post_order_traversal(root->left, handler);
			post_order_traversal(root->right, handler);
			handler(root->key, root->value);
		}
		void breadth_first_traversal(SplayTreeNode * root, Handler handler) {
			if (!root) return;
			std::queue <SplayTreeNode *> queue;
			queue.push(root);
			while (!queue.empty()) {
				SplayTreeNode * root{ queue.front() };
				handler(root->key, root->value);
				queue.pop();
				if (root->left) queue.push(root->left);
				if (root->right) queue.push(root->right);
			}
		}

	private:
		SplayTreeNode * minimum(SplayTreeNode * root) {
			if (!root) return nullptr;
			while (root->left) root = root->left;
			return root;
		}
		SplayTreeNode * maximum(SplayTreeNode * root) {
			if (!root) return nullptr;
			while (root->right) root = root->right;
			return root;
		}

	private:
		int height(const SplayTreeNode * root) {
			if (!root) return 0;
			return std::max(height(root->left), height(root->right)) + 1;
		}
		int size(const SplayTreeNode * root) {
			if (!root) return 0;
			return size(root->left) + size(root->right) + 1;
		}

	private:
		void rotate_right(SplayTreeNode * rotation_root) {
			SplayTreeNode * new_root{ rotation_root->left };
			SplayTreeNode * orphan_subtree{ new_root->right };
			rotation_root->left = orphan_subtree;
			if (orphan_subtree) {
				orphan_subtree->parent = rotation_root;
			}
			new_root->right = rotation_root;
			if (!rotation_root->parent) {
				tree_root = new_root;
			}
			else if (rotation_root == rotation_root->parent->left) {
				rotation_root->parent->left = new_root;
			}
			else if (rotation_root == rotation_root->parent->right) {
				rotation_root->parent->right = new_root;
			}
			new_root->parent = rotation_root->parent;
			rotation_root->parent = new_root;
		}
		void rotate_left(SplayTreeNode * rotation_root) {
			SplayTreeNode * new_root{ rotation_root->right };
			SplayTreeNode * orphan_subtree{ new_root->left };
			rotation_root->right = orphan_subtree;
			if (orphan_subtree) {
				orphan_subtree->parent = rotation_root;
			}
			new_root->left = rotation_root;
			if (!rotation_root->parent) {
				tree_root = new_root;
			}
			else if (rotation_root == rotation_root->parent->left) {
				rotation_root->parent->left = new_root;
			}
			else {
				rotation_root->parent->right = new_root;
			}
			new_root->parent = rotation_root->parent;
			rotation_root->parent = new_root;
		}

	private:
		void fix(SplayTreeNode * root) {
			while (root->parent) {
				if (!root->parent->parent) {
					if (root->parent->left == root) {
						rotate_right(root->parent);
					}
					else if (root->parent->right == root) {
						rotate_left(root->parent);
					}
				}
				else if (root->parent->left == root && root->parent->parent->left == root->parent) {
					rotate_right(root->parent->parent);
					rotate_right(root->parent);
				}
				else if (root->parent->right == root && root->parent->parent->right == root->parent) {
					rotate_left(root->parent->parent);
					rotate_left(root->parent);
				}
				else if (root->parent->left == root && root->parent->parent->right == root->parent) {
					rotate_right(root->parent);
					rotate_left(root->parent);
				}
				else if (root->parent->right == root && root->parent->parent->left == root->parent) {
					rotate_left(root->parent);
					rotate_right(root->parent);
				}
			}
		}

	private:
		void clear(SplayTreeNode * root) {
			if (!root) return;
			if (root->left) clear(root->left);
			if (root->right) clear(root->right);
			delete root;
			root = nullptr;
		}

	public:
		SplayTree() = default;
		explicit SplayTree(Pairs pairs) {
			for (auto pair : pairs) {
				insert(pair.first, pair.second);
			}
		}
		SplayTree(const SplayTree &) = delete;
		SplayTree(SplayTree &&) = delete;
		~SplayTree() {
			clear();
		}

	public:
		SplayTree & operator=(const SplayTree &) = delete;
		SplayTree & operator=(SplayTree &&) = delete;

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
		SplayTreeNode * minimum() {
			return minimum(tree_root);
		}
		SplayTreeNode * maximum() {
			return maximum(tree_root);
		}

	public:
		int height() {
			return height(tree_root);
		}
		int size() {
			return size(tree_root);
		}

	public:
		void insert(const Key & key, const Value & value) {
			SplayTreeNode * current{ tree_root };
			SplayTreeNode * parent{ nullptr };
			while (current) {
				parent = current;
				if (key > current->key) {
					current = current->right;
				}
				else if (key < current->key) {
					current = current->left;
				}
				else if (key == current->key) {
					current->value = value;
					return;
				}
			}
			current = new SplayTreeNode(key, value);
			current->parent = parent;
			if (!parent) {
				tree_root = current;
			}
			else if (current->key > parent->key) {
				parent->right = current;
			}
			else if (current->key < parent->key) {
				parent->left = current;
			}
			fix(current);
		}
		SplayTreeNode * search(const Key & key) {
			SplayTreeNode * current{ tree_root };
			while (current) {
				if (key > current->key) {
					current = current->right;
				}
				else if (key < current->key) {
					current = current->left;
				}
				else {
					return current;
				}
			}
			return nullptr;
		}

	public:
		void clear() {
			clear(tree_root);
			tree_root = nullptr;
		}
	};
}