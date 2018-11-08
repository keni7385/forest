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

#include <vector>
#include <algorithm>

namespace forest {
	template <typename T, unsigned K>
	class QuadTree {
	private:
		template <typename T>
		class Point {
			template<typename U> friend class Rectangle;

		private:
			T x;
			T y;

		public:
			Point() = default;
			Point(const T & X, const T & Y) : x(X), y(Y) { }
			~Point() = default;

		public:
			void setX(const T & X) {
				x = X;
			}
			void setY(const T & Y) {
				y = Y;
			}

		public:
			T getX() const {
				return x;
			}
			T getY() const {
				return y;
			}

		public:
			friend bool operator == (const Point<T> & lhs, const Point<T> & rhs) {
				return lhs.x == rhs.x && lhs.y == rhs.y;
			}
		};

	private:
		template <typename T>
		class Rectangle {
			template<typename U, unsigned K> friend class QuadTree;

		private:
			T x;
			T y;
			T w;
			T h;

		public:
			Rectangle() = default;
			Rectangle(const T & X, const T & Y, const T & W, const T & H) : x(X), y(Y), w(W), h(H) { }
			~Rectangle() = default;

		public:
			void setX(const T & X) {
				x = X;
			}
			void setY(const T & Y) {
				y = Y;
			}
			void setW(const T & W) {
				w = W;
			}
			void setH(const T & H) {
				h = H;
			}

		public:
			T getX() const {
				return x;
			}
			T getY() const {
				return y;
			}
			T getW() const {
				return w;
			}
			T getH() const {
				return h;
			}

		public:
			bool contains(const Point <T> & point) const {
				return point.x >= x - w && point.x <= x + w && point.y >= y - h && point.y <= y + h;
			}
			bool intersects(const Rectangle <T> & other) const {
				return !(x - w > other.x + other.w || x + w < other.x - other.w || y - h > other.y + other.h || y + h < other.y - other.h);
			}
		};

	private:
		std::vector <Point <T>> children;

	private:
		Rectangle <T> boundary;

	private:
		bool subdivided{ false };

	private:
		QuadTree * NW{ nullptr };
		QuadTree * NE{ nullptr };
		QuadTree * SW{ nullptr };
		QuadTree * SE{ nullptr };

	private:
		void subdivide() {
			const T half_w = boundary.w / 2;
			const T half_h = boundary.h / 2;

			NW = new QuadTree(boundary.x - half_w, boundary.y + half_h, half_w, half_h);
			NE = new QuadTree(boundary.x + half_w, boundary.y + half_h, half_w, half_h);
			SW = new QuadTree(boundary.x - half_w, boundary.y - half_h, half_w, half_h);
			SE = new QuadTree(boundary.x + half_w, boundary.y - half_h, half_w, half_h);

			subdivided = true;
		}

	private:
		void query(const Rectangle <T> & area, std::vector <Point<T>> & results) const {
			if (!area.intersects(boundary)) return;
			if (subdivided) {
				NW->query(area, results);
				NE->query(area, results);
				SW->query(area, results);
				SE->query(area, results);
			}
			else {
				for (auto child : children) {
					if (area.contains(child)) {
						results.push_back(child);
					}
				}
			}
		}

	public:
		QuadTree() = delete;
		QuadTree(const T & X, const T & Y, const T & W, const T & H) {
			boundary.x = X;
			boundary.y = Y;
			boundary.w = W;
			boundary.h = H;
		};
		~QuadTree() {
			clear();
		}

	public:
		bool insert(const Point <T> & point) {
			if (!boundary.contains(point)) return false;
			if (!subdivided) {
				children.push_back(point);
				if (children.size() > K) {
					subdivide();
					typename std::vector <Point<T>>::iterator it = children.begin();
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
			else {
				if (NW->insert(point)) return true;
				else if (NE->insert(point)) return true;
				else if (SW->insert(point)) return true;
				else if (SE->insert(point)) return true;
				return false;
			}
		}
		std::vector<Point<T>> query(const Rectangle <T> & area) {
			std::vector <Point<T>> results;
			query(area, results);
			return results;
		}
		bool search(const Point <T> & point) {
			if (!boundary.contains(point)) return false;
			if (subdivided) {
				if (NW->search(point)) return true;
				else if (NE->search(point)) return true;
				else if (SW->search(point)) return true;
				else if (SE->search(point)) return true;
				else return false;
			}
			else {
				if (std::find(children.begin(), children.end(), point) != children.end()) {
					return true;
				}
				else {
					return false;
				}
			}
		}

	public:
		void clear() {
			if (!this) return;
			if (subdivided == true) {
				NW->clear();
				NE->clear();
				SW->clear();
				SE->clear();
			}
			subdivided = false;
			children.clear();
			delete NW;
			delete NE;
			delete SW;
			delete SE;
			NW = nullptr;
			NE = nullptr;
			SW = nullptr;
			SE = nullptr;
		}
	};
}