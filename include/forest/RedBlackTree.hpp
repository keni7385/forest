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
	class RedBlackTree {
	public:
		using Pair = std::pair <Key, Value>;
		using Pairs = std::initializer_list<Pair>;
		using Handler = std::function <void(const Key &, const Value &)>;

	private:
		enum Color {
			RED,
			BLACK
		};
		class RedBlackTreeNode {
			friend class RedBlackTree;

		private:
			RedBlackTreeNode * parent{ nullptr };
			RedBlackTreeNode * left{ nullptr };
			RedBlackTreeNode * right{ nullptr };

		private:
			Color color;

		public:
			Key key;
			Value value;

		public:
			RedBlackTreeNode() = default;
			RedBlackTreeNode(const Key & KEY, const Value & VALUE, const Color & COLOR) : key(KEY), value(VALUE), color(COLOR) { }
			RedBlackTreeNode(const RedBlackTreeNode &) = delete;
			RedBlackTreeNode(RedBlackTreeNode &&) = delete;
			~RedBlackTreeNode() = default;

		public:
			RedBlackTreeNode & operator=(const RedBlackTreeNode &) = delete;
			RedBlackTreeNode & operator=(RedBlackTreeNode &&) = delete;
		};

	private:
		RedBlackTreeNode * tree_root{ nullptr };

	private:
		void pre_order_traversal(const RedBlackTreeNode * root, Handler handler) {
			if (!root) return;
			handler(root->key, root->value);
			pre_order_traversal(root->left, handler);
			pre_order_traversal(root->right, handler);
		}
		void in_order_traversal(const RedBlackTreeNode * root, Handler handler) {
			if (!root) return;
			in_order_traversal(root->left, handler);
			handler(root->key, root->value);
			in_order_traversal(root->right, handler);
		}
		void post_order_traversal(const RedBlackTreeNode * root, Handler handler) {
			if (!root) return;
			post_order_traversal(root->left, handler);
			post_order_traversal(root->right, handler);
			handler(root->key, root->value);
		}
		void breadth_first_traversal(const RedBlackTreeNode * root, Handler handler) {
			std::queue <const RedBlackTreeNode *> queue;
			if (!root) return;
			queue.push(root);
			while (!queue.empty()) {
				RedBlackTreeNode * current{ queue.front() };
				handler(current->key, current->value);
				queue.pop();
				if (current->left) queue.push(current->left);
				if (current->right) queue.push(current->right);
			}
		}

	private:
		RedBlackTreeNode * minimum(RedBlackTreeNode * root) {
			if (!root) return nullptr;
			while (root->left) root = root->left;
			return root;
		}
		RedBlackTreeNode * maximum(RedBlackTreeNode * root) {
			if (!root) return nullptr;
			while (root->right) root = root->right;
			return root;
		}

	private:
		unsigned height(const RedBlackTreeNode * root) {
			if (!root) return 0;
			return std::max(height(root->left), height(root->right)) + 1;
		}
		unsigned size(const RedBlackTreeNode * root) {
			if (!root) return 0;
			return size(root->left) + size(root->right) + 1;
		}

	private:
		void rotate_right(RedBlackTreeNode * rotation_root) {
			RedBlackTreeNode * new_root{ rotation_root->left };
			RedBlackTreeNode * orphan_subtree{ new_root->right };
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
		void rotate_left(RedBlackTreeNode * rotation_root) {
			RedBlackTreeNode * new_root{ rotation_root->right };
			RedBlackTreeNode * orphan_subtree{ new_root->left };
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
		void fix(RedBlackTreeNode * root) {
			RedBlackTreeNode * parent{ nullptr };
			RedBlackTreeNode * grand_parent{ nullptr };
			while ((root != tree_root) && (root->color != BLACK) && (root->parent->color == RED)) {
				parent = root->parent;
				grand_parent = root->parent->parent;
				if (parent == grand_parent->left) {
					RedBlackTreeNode * uncle{ grand_parent->right };
					if (uncle && uncle->color == RED) {
						grand_parent->color = RED;
						parent->color = BLACK;
						uncle->color = BLACK;
						root = grand_parent;
					}
					else {
						if (root == parent->right) {
							rotate_left(parent);
							root = parent;
							parent = root->parent;
						}
						rotate_right(grand_parent);
						std::swap(parent->color, grand_parent->color);
						root = parent;
					}
				}
				else {
					RedBlackTreeNode * uncle{ grand_parent->left };
					if (uncle && (uncle->color == RED)) {
						grand_parent->color = RED;
						parent->color = BLACK;
						uncle->color = BLACK;
						root = grand_parent;
					}
					else {
						if (root == parent->left) {
							rotate_right(parent);
							root = parent;
							parent = root->parent;
						}
						rotate_left(grand_parent);
						std::swap(parent->color, grand_parent->color);
						root = parent;
					}
				}
			}
			tree_root->color = BLACK;
		}

	private:
		void clear(RedBlackTreeNode * root) {
			if (!root) return;
			if (root->left) clear(root->left);
			if (root->right) clear(root->right);
			delete root;
			root = nullptr;
		}

	public:
		RedBlackTree() = default;
		explicit RedBlackTree(Pairs pairs) {
			for (auto pair : pairs) {
				insert(pair.first, pair.second);
			}
		}
		RedBlackTree(const RedBlackTree &) = delete;
		RedBlackTree(RedBlackTree &&) = delete;
		~RedBlackTree() {
			clear();
		}
	public:
		RedBlackTree & operator=(const RedBlackTree &) = delete;
		RedBlackTree & operator=(RedBlackTree &&) = delete;

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
		RedBlackTreeNode * minimum() {
			return minimum(tree_root);
		}
		RedBlackTreeNode * maximum() {
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
			RedBlackTreeNode * current{ tree_root };
			RedBlackTreeNode * parent{ nullptr };
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
			current = new RedBlackTreeNode(key, value, RED);
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
		RedBlackTreeNode * search(const Key & key) {
			RedBlackTreeNode * current{ tree_root };
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