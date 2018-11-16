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
#include <array>
#include <functional>
#include <vector>

namespace forest {
	template <typename Arithmetic, int Dimensions = 1>
	class KDTree {
		static_assert(Dimensions > 0, "Invalid KDTree Dimensions");

	public:
		using Point = std::array<Arithmetic, Dimensions>;
		using Points = std::vector<Point>;
		using PointsIt = typename Points::iterator;
		using Handler = std::function<void(const Point &)>;

	public:
		class Range {
			static_assert(Dimensions > 0, "Invalid Range Dimensions");

			template <typename T, int K> friend class KDTree;

		private:
			Point origin;
			Point transform;

		public:
			Range() = default;
			Range(const Point & ORIGIN, const Point & TRANSFORM) : origin(ORIGIN), transform(TRANSFORM) { }
			Range(const Range &) = delete;
			Range(Range &&) = delete;
			~Range() = default;

		public:
			Range & operator=(const Range &) = delete;
			Range & operator=(Range &&) = delete;

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
				for (int i = 0; i < Dimensions; ++i) {
					if (!(point[i] >= origin[i] - transform[i] && point[i] <= origin[i] + transform[i])) {
						return false;
					}
				}
				return true;
			}
			bool intersects(const Range & other) const {
				for (int i = 0; i < Dimensions; ++i) {
					if (!(origin[i] - transform[i] <= other.origin[i] + other.transform[i] && origin[i] + transform[i] >= other.origin[i] - other.transform[i])) {
						return false;
					}
				}
				return true;
			}
		};

	private:
		class KDTreeNode {
			friend class KDTree;

		public:
			Point point;

		private:
			KDTreeNode * left{ nullptr };
			KDTreeNode * right{ nullptr };

		public:
			KDTreeNode() = default;
			KDTreeNode(const PointsIt begin, const PointsIt end, const unsigned depth) {
				if (std::distance(begin, end) == 0) return;
				unsigned current = depth % Dimensions;
				if (std::distance(begin, end) >= 2) {
					std::sort(begin, end, [current](const Point & lhs, const Point & rhs) {
						return lhs[current] < rhs[current];
					});
					left = new KDTreeNode(begin, begin + std::distance(begin, end) / 2, depth + 1);
					right = new KDTreeNode(begin + std::distance(begin, end) / 2 + 1, end, depth + 1);
				}
				point = *(begin + std::distance(begin, end) / 2);
			}
			KDTreeNode(const KDTreeNode &) = delete;
			KDTreeNode(KDTreeNode &&) = delete;
			~KDTreeNode() = default;

		public:
			KDTreeNode & operator=(const KDTreeNode &) = delete;
			KDTreeNode & operator=(KDTreeNode &&) = delete;
		};

	private:
		KDTreeNode * tree_root{ nullptr };

	private:
		KDTreeNode * minimum(KDTreeNode * x, KDTreeNode * y, const unsigned dimension) noexcept {
			if (x && y) {
				if (x->point.empty() || y->point.empty()) return nullptr;
				if (x->point[dimension] <= y->point[dimension]) {
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
		KDTreeNode * minimum(KDTreeNode * x, KDTreeNode * y, KDTreeNode * z, const unsigned dimension) {
			return minimum(x, minimum(y, z, dimension), dimension);
		}
		KDTreeNode * minimum(KDTreeNode * root, const unsigned dimension, const unsigned depth) {
			if (!root) return nullptr;
			unsigned current = depth % Dimensions;
			if (current == dimension) {
				if (!root->left) return root;
				return minimum(root->left, dimension, depth + 1);
			}
			return minimum(root, minimum(root->left, dimension, depth + 1), minimum(root->right, dimension, depth + 1), dimension);
		}
		KDTreeNode * minimum(KDTreeNode * root, const unsigned dimension) {
			return minimum(root, dimension, 0);
		}

	private:
		KDTreeNode * maximum(KDTreeNode * x, KDTreeNode * y, const unsigned dimension) {
			if (x && y) {
				if (x->point.empty() || y->point.empty()) return nullptr;
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
		KDTreeNode * maximum(KDTreeNode * x, KDTreeNode * y, KDTreeNode * z, const unsigned dimension) {
			return maximum(x, maximum(y, z, dimension), dimension);
		}
		KDTreeNode * maximum(KDTreeNode * root, const unsigned dimension, const unsigned depth) {
			if (!root) return nullptr;
			unsigned current = depth % Dimensions;
			if (current == dimension) {
				if (!root->right) return root;
				return maximum(root->right, dimension, depth + 1);
			}
			return maximum(root, maximum(root->left, dimension, depth + 1), maximum(root->right, dimension, depth + 1), dimension);
		}
		KDTreeNode * maximum(KDTreeNode * root, const unsigned dimension) {
			return maximum(root, dimension, 0);
		}

	private:
		unsigned size(const KDTreeNode * root) {
			if (!root) return 0;
			return size(root->left) + size(root->right) + 1;
		}

	private:
		bool search(const KDTreeNode * root, const Point & point, const unsigned depth) {
			if (!root) return false;
			unsigned current = depth % Dimensions;
			if (root->point.empty()) return false;
			if (point == root->point) {
				return true;
			}
			else if (point[current] <= root->point[current]) {
				return search(root->left, point, depth + 1);
			}
			else {
				return search(root->right, point, depth + 1);
			}
			return false;
		}
		KDTreeNode * remove(KDTreeNode * root, const Point & point, const unsigned depth) {
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
					root->point = min->point;
					root->right = remove(root->right, min->point, depth + 1);
				}
				else {
					KDTreeNode * min = minimum(root->left, current);
					root->point = min->point;
					root->left = remove(root->left, min->point, depth + 1);
				}
			}
			else {
				if (point[current] <= root->point[current]) {
					root->left = remove(root->left, point, depth + 1);
				}
				else {
					root->right = remove(root->right, point, depth + 1);
				}
			}
			return root;
		}
		void query(const KDTreeNode * root, const Range & range, Handler handler) {
			if (!root) return;
			if (range.contains(root->point)) {
				handler(root->point);
			}
			query(root->left, range, handler);
			query(root->right, range, handler);
		}

	private:
		void clear(KDTreeNode * root) {
			if (!root) return;
			if (root->left) clear(root->left);
			if (root->right) clear(root->right);
			delete root;
			root = nullptr;
		}

	public:
		KDTree() = default;
		KDTree(const PointsIt begin, const PointsIt end) {
			fill(begin, end);
		}
		KDTree(const KDTree &) = delete;
		KDTree(KDTree &&) = delete;
		~KDTree() {
			clear();
		}

	public:
		KDTree & operator=(const KDTree &) = delete;
		KDTree & operator=(KDTree &&) = delete;

	public:
		KDTreeNode * minimum(const unsigned dimension) {
			return minimum(tree_root, dimension);
		}
		KDTreeNode * maximum(const unsigned dimension) {
			return maximum(tree_root, dimension);
		}

	public:
		unsigned size() {
			return size(tree_root);
		}

	public:
		void fill(const PointsIt begin, const PointsIt end) {
			if (!tree_root) tree_root = new KDTreeNode(begin, end, 0);
		}
		bool search(const Point & point) {
			return search(tree_root, point, 0);
		}
		void remove(const Point & point) {
			tree_root = remove(tree_root, point, 0);
		}
		void query(const Range & range, Handler handler) {
			query(tree_root, range, handler);
		}

	public:
		void clear() {
			clear(tree_root);
			tree_root = nullptr;
		}
	};
	template <typename T> using Tree1D = KDTree<T, 1>;
	template <typename T> using Tree2D = KDTree<T, 2>;
	template <typename T> using Tree3D = KDTree<T, 3>;
}