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
#include <vector>
#include <algorithm>
#include <memory>

namespace forest {
	template <typename Arithmetic, unsigned Dimensions>
	class KDTree {
	public:
		using Point = std::vector<Arithmetic>;
		using Points = std::vector<Point>;

	public:
		template <typename RArithmetic, unsigned RDimensions>
		class Range {
			static_assert(RDimensions > 0, "Invalid Range Dimensions");

		public:
			using Point = std::vector<RArithmetic>;

		private:
			Point origin;
			Point transform;

		public:
			Range() = default;
			Range(const Point & ORIGIN, const Point & TRANSFORM) : origin(ORIGIN), transform(TRANSFORM) { }
			~Range() = default;

		public:
			void setOrigin(const Point & ORIGIN) {
				origin = ORIGIN;
			}
			void setTransform(const Point & TRANSFORM) {
				transform = TRANSFORM;
			}

		public:
			Point getOrigin() const {
				return origin;
			}
			Point getTransform() const {
				return transform;
			}

		public:
			bool contains(const Point & point) const {
				bool flag = true;
				for (unsigned i = 0; i < RDimensions; ++i) {
					if (!(point[i] >= origin[i] - transform[i] && point[i] <= origin[i] + transform[i])) {
						flag = false;
						break;
					}
				}
				return flag;
			}
			bool intersects(const Range & other) const {
				bool flag = false;
				for (unsigned i = 0; i < RDimensions; ++i) {
					if (origin[i] - transform[i] <= other.origin[i] + other.transform[i] && origin[i] + transform[i] >= other.origin[i] - other.transform[i]) {
						flag = true;
						break;
					}
				}
				return flag;
			}
		};

	private:
		class KDTreeNode {
			friend class KDTree;

		private:
			KDTreeNode * left{ nullptr };
			KDTreeNode * right{ nullptr };

		public:
			Point point;

		public:
			KDTreeNode() = default;
			explicit KDTreeNode(const Point & POINT) : point(POINT) { }
			~KDTreeNode() = default;
		};

	private:
		KDTreeNode * tree_root{ nullptr };

	private:
		KDTreeNode * insert(KDTreeNode * root, const Point & point, unsigned depth) noexcept {
			if (!root) return new KDTreeNode(point);
			unsigned current = depth % Dimensions;
			if (point[current] < (root->point[current])) {
				root->left = insert(root->left, point, depth + 1);
			}
			else {
				root->right = insert(root->right, point, depth + 1);
			}
			return root;
		}
		KDTreeNode * search(KDTreeNode * root, const Point & point, unsigned depth) noexcept {
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
		KDTreeNode * remove(KDTreeNode * root, const Point & point, unsigned depth) {
			if (!root) return nullptr;

			int current = depth % Dimensions;

			if (point == root->point) {
				if (!root->left && !root->right) {
					delete root;
					root = nullptr;
					return root;
				}
				if (root->right) {
					KDTreeNode * min = minimum(root->right, current);
					if (root && min)
						std::swap(root->point, min->point);
					root->right = remove(root->right, min->point, depth + 1);
				}
				else {
					KDTreeNode *min = minimum(root->left, current);
					if (root && min)
						std::swap(root->point, min->point);
					root->left = remove(root->left, min->point, depth + 1);
				}
			}
			else {
				if (point[current] < root->point[current]) {
					root->left = remove(root->left, point, depth + 1);
				}
				else {
					root->right = remove(root->right, point, depth + 1);
				}
			}

			return root;
		}
		void query(KDTreeNode * root, const Range <Arithmetic, Dimensions> & area, Points & results) noexcept {
			if (!root) return;
			if (area.contains(root->point)) {
				results.push_back(root->point);
			}
			query(root->left, area, results);
			query(root->right, area, results);
		}
	private:
		KDTreeNode * minimum(KDTreeNode * x, KDTreeNode * y, unsigned dimension) noexcept {
			if (x && y) {
				if (x->point[dimension] < y->point[dimension]) {
					return x;
				}
				else {
					return y;
				}
			}
			else if (x) return x;
			else if (y) return y;
			else return nullptr;
		}
		KDTreeNode * minimum(KDTreeNode * x, KDTreeNode * y, KDTreeNode * z, unsigned dimension) noexcept {
			return minimum(x, minimum(y, z, dimension), dimension);
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
		KDTreeNode * maximum(KDTreeNode * x, KDTreeNode * y, unsigned dimension) noexcept {
			if (x && y) {
				if (x->point[dimension] > y->point[dimension]) {
					return x;
				}
				else {
					return y;
				}
			}
			else if (x) return x;
			else if (y) return y;
			else return nullptr;
		}
		KDTreeNode * maximum(KDTreeNode * x, KDTreeNode * y, KDTreeNode * z, unsigned dimension) noexcept {
			return maximum(x, maximum(y, z, dimension), dimension);
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
		void insert(const Point & point) noexcept {
			tree_root = insert(tree_root, point, 0);
		}
		KDTreeNode * search(const Point & point) noexcept {
			return search(tree_root, point, 0);
		}
		void remove(const Point & point) {
			tree_root = remove(tree_root, point, 0);
		}
		Points query(const Range <Arithmetic, Dimensions> & area) noexcept {
			Points results;
			query(tree_root, area, results);
			return results;
		}

	public:
		KDTreeNode * minimum(unsigned dimension) noexcept {
			return minimum(tree_root, dimension, 0);
		}
		KDTreeNode * maximum(unsigned dimension) noexcept {
			return maximum(tree_root, dimension, 0);
		}

	public:
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