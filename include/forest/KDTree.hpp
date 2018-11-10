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

#include <array>
#include <algorithm>
#include <memory>

namespace forest {
	template <typename Arithmetic, unsigned Dimensions>
	class KDTree {
	private:
		class KDTreeNode {
			friend class KDTree;

		private:
			KDTreeNode * left{ nullptr };
			KDTreeNode * right{ nullptr };

		private:
			unsigned height{ 1 };

		public:
			std::array<Arithmetic, Dimensions> point;

		public:
			KDTreeNode() = default;
			explicit KDTreeNode(const std::array <Arithmetic, Dimensions> & POINT) : point(POINT) { }
			~KDTreeNode() = default;
		};

	private:
		KDTreeNode * tree_root{ nullptr };

	private:
		KDTreeNode * insert(KDTreeNode * root, const std::array <Arithmetic, Dimensions> & point, unsigned depth) noexcept {
			if (!root) return new KDTreeNode(point);
			unsigned current = depth % Dimensions;
			if (point[current] < (root->point[current])) {
				root->left = insert(root->left, point, depth + 1);
			}
			else {
				root->right = insert(root->right, point, depth + 1);
			}
			root->height = std::max(height(root->left), height(root->right)) + 1;
			return root;
		}
		KDTreeNode * search(KDTreeNode * root, const std::array<Arithmetic, Dimensions> & point, unsigned depth) noexcept {
			if (!root) return nullptr;
			if (root->point == point) return root;
			unsigned current = depth % Dimensions;
			if (point[current] < root->point[current]) {
				return search(root->left, point, depth + 1);
			}
			else {
				return search(root->right, point, depth + 1);
			}
		}

	private:
		KDTreeNode * minimum(KDTreeNode * x, KDTreeNode * y, KDTreeNode * z, unsigned dimension) noexcept {
			KDTreeNode * tmp = x;
			if (y && y->point[dimension] < tmp->point[dimension]) tmp = y;
			if (z && z->point[dimension] < tmp->point[dimension]) tmp = z;
			return tmp;
		}
		KDTreeNode * minimum(KDTreeNode * root, unsigned dimension, unsigned depth) noexcept {
			if (!root) return nullptr;
			unsigned current = depth % Dimensions;
			if (current == dimension) {
				if (!root->left) return root;
				return minimum(root->left, dimension, depth + 1);
			}
			return minimum(root, minimum(root->left, dimension, depth + 1), minimum(root->right, dimension, depth + 1), dimension);
		}
		KDTreeNode * minimum(KDTreeNode * root, unsigned dimension) noexcept {
			return minimum(root, dimension, 0);
		}

	private:
		KDTreeNode * maximum(KDTreeNode * x, KDTreeNode * y, KDTreeNode * z, unsigned dimension) noexcept {
			KDTreeNode * tmp = x;
			if (y && y->point[dimension] > tmp->point[dimension]) tmp = y;
			if (z && z->point[dimension] > tmp->point[dimension]) tmp = z;
			return tmp;
		}
		KDTreeNode * maximum(KDTreeNode * root, unsigned dimension, unsigned depth) noexcept {
			if (!root) return nullptr;
			unsigned current = depth % Dimensions;
			if (current == dimension) {
				if (!root->right) return root;
				return maximum(root->right, dimension, depth + 1);
			}
			return maximum(root, maximum(root->left, dimension, depth + 1), maximum(root->right, dimension, depth + 1), dimension);
		}
		KDTreeNode * maximum(KDTreeNode * root, unsigned dimension) noexcept {
			return maximum(root, dimension, 0);
		}

	private:
		unsigned height(const KDTreeNode * root) noexcept {
			if (!root) return 0;
			return root->height;
		}
		unsigned size(const KDTreeNode * root) noexcept {
			if (!root) return 0;
			return size(root->left) + size(root->right) + 1;
		}

	private:
		void clear(KDTreeNode * root) noexcept {
			if (!root) return;
			if (root->left) clear(root->left);
			if (root->right) clear(root->right);
			delete root;
			root = nullptr;
		}

	public:
		KDTree() = default;
		~KDTree() {
			clear();
		}

	public:
		void insert(const std::array <Arithmetic, Dimensions> & point) noexcept {
			tree_root = insert(tree_root, point, 0);
		}
		KDTreeNode * search(const std::array <Arithmetic, Dimensions> & point) noexcept {
			return search(tree_root, point, 0);
		}

	public:
		KDTreeNode * minimum(unsigned dimension) noexcept {
			return minimum(tree_root, dimension, 0);
		}
		KDTreeNode * maximum(unsigned dimension) noexcept {
			return maximum(tree_root, dimension, 0);
		}

	public:
		unsigned height() noexcept {
			return height(tree_root);
		}
		unsigned size() noexcept {
			return size(tree_root);
		}

	public:
		void clear() noexcept {
			clear(tree_root);
			tree_root = nullptr;
		}
	};

	template <typename Arithmetic> using Tree1D = KDTree<Arithmetic, 1>;
	template <typename Arithmetic> using Tree2D = KDTree<Arithmetic, 2>;
	template <typename Arithmetic> using Tree3D = KDTree<Arithmetic, 3>;
}