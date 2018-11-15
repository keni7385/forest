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
	template <typename Arithmetic, int Capacity = 1>
	class QuadTree {
		static_assert(Capacity > 0, "Invalid QuadTree Dimensions");

	public:
		using Point = std::array <Arithmetic, 2>;
		using Points = std::vector <Point>;
		using PointsIt = typename std::vector <Point>::iterator;

	public:
		class Range {
			template <typename T, int K> friend class QuadTree;

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
			void setY(const Point & TRANSFORM) {
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
				return point[0] >= origin[0] - transform[0] &&
					   point[0] <= origin[0] + transform[0] &&
					   point[1] >= origin[1] - transform[1] &&
					   point[1] <= origin[1] + transform[1];
			}
			//bool contains(const Point & point) const {
			//	for (int i = 0; i < 2; ++i) {
			//		if (!(point[i] >= origin[i] - transform[i] && point[i] <= origin[i] + transform[i])) {
			//			return false;
			//		}
			//	}
			//	return true;
			//}
			bool intersects(const Range & other) const {
				return origin[0] - transform[0] <= other.origin[0] + other.transform[0] &&
					   origin[0] + transform[0] >= other.origin[0] - other.transform[0] &&
					   origin[1] - transform[1] <= other.origin[1] + other.transform[1] &&
					   origin[1] + transform[1] >= other.origin[1] - other.transform[1];
			}
			//bool intersects(const Range & other) const {
			//	for (int i = 0; i < 2; ++i) {
			//		if (!(origin[i] - transform[i] <= other.origin[i] + other.transform[i] && origin[i] + transform[i] >= other.origin[i] - other.transform[i])) {
			//			return false;
			//		}
			//	}
			//	return true;
			//}
		};

	private:
		Points children;

	private:
		Range boundary;

	private:
		bool divided{ false };

	private:
		QuadTree * NW{ nullptr };
		QuadTree * NE{ nullptr };
		QuadTree * SW{ nullptr };
		QuadTree * SE{ nullptr };

	private:
		void divide() noexcept {
			NW = new QuadTree <Arithmetic, Capacity>({
				{ boundary.origin[0] - boundary.transform[0] / 2, boundary.origin[1] + boundary.transform[1] / 2 }, 
				{ boundary.transform[0] / 2, boundary.transform[1] / 2 }
			});
			NE = new QuadTree <Arithmetic, Capacity>({
				{ boundary.origin[0] + boundary.transform[0] / 2, boundary.origin[1] + boundary.transform[1] / 2 },
				{ boundary.transform[0] / 2, boundary.transform[1] / 2 }
			});
			SW = new QuadTree <Arithmetic, Capacity>({
				{ boundary.origin[0] - boundary.transform[0] / 2, boundary.origin[1] - boundary.transform[1] / 2 },
				{ boundary.transform[0] / 2, boundary.transform[1] / 2 }
			});
			SE = new QuadTree <Arithmetic, Capacity>({
				{ boundary.origin[0] + boundary.transform[0] / 2, boundary.origin[1] - boundary.transform[1] / 2 },
				{ boundary.transform[0] / 2, boundary.transform[1] / 2 }
			});
			divided = true;
		}
		void merge() noexcept {
			delete NW;
			delete NE;
			delete SW;
			delete SE;
			NW = nullptr;
			NE = nullptr;
			SW = nullptr;
			SE = nullptr;
			divided = false;
		}

	public:
		QuadTree() = delete;
		QuadTree(const Range & BOUNDARY) : boundary(BOUNDARY) { }
		~QuadTree() {
			clear();
		}

	public:
		bool insert(const Point & point) noexcept {
			if (!boundary.contains(point)) return false;
			if (!divided) {
				children.push_back(point);
				if (children.size() > Capacity) {
					divide();
					PointsIt it = children.begin();
					while (it != children.end()) {
						if (NW->boundary.contains(*it)) NW->insert(*it);
						else if (NE->boundary.contains(*it)) NE->insert(*it);
						else if (SW->boundary.contains(*it)) SW->insert(*it);
						else if (SE->boundary.contains(*it)) SE->insert(*it);
						it = children.erase(it);
					}
				}
				return true;
			}
			return NW->insert(point) || NE->insert(point) || SW->insert(point) || SE->insert(point);
		}
		bool remove(const Point & point) {
			if (!boundary.contains(point)) return false;
			if (!divided) {
				children.erase(std::remove(children.begin(), children.end(), point), children.end());
				return true;
			}
			if (NW->remove(point) || NE->remove(point) || SW->remove(point) || SE->remove(point)) {
				if (!NW->divided && !NE->divided && !SW->divided && !SE->divided) {
					if (NW->children.empty() && NE->children.empty() && SW->children.empty() && SE->children.empty()) {
						merge();
					}
				}
				return true;
			}
			return false;
		}
		bool search(const Point & point) noexcept {
			if (!boundary.contains(point)) return false;
			if (divided) {
				return NW->search(point) || NE->search(point) || SW->search(point) || SE->search(point);
			}
			else {
				return std::find(children.begin(), children.end(), point) != children.end();
			}
		}
		void query(const Range & range, std::function<void(const Point &)> handler) noexcept {
			if (!range.intersects(boundary)) return;
			if (divided) {
				NW->query(range, handler);
				NE->query(range, handler);
				SW->query(range, handler);
				SE->query(range, handler);
			}
			else {
				for (auto child : children) {
					if (range.contains(child)) {
						handler(child);
					}
				}
			}
		}

	public:
		void clear() noexcept {
			if (divided == true) {
				NW->clear();
				NE->clear();
				SW->clear();
				SE->clear();
			}
			children.clear();
			merge();
		}
	};
}