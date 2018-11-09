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
	template <typename Arithmetic, unsigned Capacity>
	class QuadTree {
	private:
		template <typename U>
		class Point {
		private:
			U x;
			U y;

		public:
			Point() = default;
			Point(const U & X, const U & Y) : x(X), y(Y) { }
			~Point() = default;

		public:
			void setX(const U & X) {
				x = X;
			}
			void setY(const U & Y) {
				y = Y;
			}

		public:
			U getX() const {
				return x;
			}
			U getY() const {
				return y;
			}

		public:
			friend bool operator == (const Point<U> & lhs, const Point<U> & rhs) {
				return lhs.x == rhs.x && lhs.y == rhs.y;
			}
		};

	private:
		template <typename U>
		class Rectangle {
			template<typename T, unsigned K> friend class QuadTree;

		private:
			U x;
			U y;
			U w;
			U h;

		public:
			Rectangle() = default;
			Rectangle(const U & X, const U & Y, const U & W, const U & H) : x(X), y(Y), w(W), h(H) { }
			~Rectangle() = default;

		public:
			void setX(const U & X) {
				x = X;
			}
			void setY(const U & Y) {
				y = Y;
			}
			void setW(const U & W) {
				w = W;
			}
			void setH(const U & H) {
				h = H;
			}

		public:
			U getX() const {
				return x;
			}
			U getY() const {
				return y;
			}
			U getW() const {
				return w;
			}
			U getH() const {
				return h;
			}

		public:
			bool contains(const Point <U> & point) const {
				return point.getX() >= x - w && point.getX() <= x + w && point.getY() >= y - h && point.getY() <= y + h;
			}
			bool intersects(const Rectangle <U> & other) const {
				return !(x - w > other.x + other.w || x + w < other.x - other.w || y - h > other.y + other.h || y + h < other.y - other.h);
			}
		};

	private:
		std::vector <Point <Arithmetic>> children;

	private:
		Rectangle <Arithmetic> boundary;

	private:
		bool subdivided{ false };

	private:
		QuadTree * NW{ nullptr };
		QuadTree * NE{ nullptr };
		QuadTree * SW{ nullptr };
		QuadTree * SE{ nullptr };

	private:
		void subdivide() noexcept {
			const Arithmetic half_w = boundary.w / 2;
			const Arithmetic half_h = boundary.h / 2;

			NW = new QuadTree(boundary.x - half_w, boundary.y + half_h, half_w, half_h);
			NE = new QuadTree(boundary.x + half_w, boundary.y + half_h, half_w, half_h);
			SW = new QuadTree(boundary.x - half_w, boundary.y - half_h, half_w, half_h);
			SE = new QuadTree(boundary.x + half_w, boundary.y - half_h, half_w, half_h);

			subdivided = true;
		}

	private:
		void query(const Rectangle <Arithmetic> & area, std::vector <Point<Arithmetic>> & results) noexcept {
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
		QuadTree(const Arithmetic & X, const Arithmetic & Y, const Arithmetic & W, const Arithmetic & H) {
			boundary.x = X;
			boundary.y = Y;
			boundary.w = W;
			boundary.h = H;
		};
		~QuadTree() {
			clear();
		}

	public:
		bool insert(const Point <Arithmetic> & point) noexcept {
			if (!boundary.contains(point)) return false;
			if (!subdivided) {
				children.push_back(point);
				if (children.size() > Capacity) {
					subdivide();
					typename std::vector <Point<Arithmetic>>::iterator it = children.begin();
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
		std::vector<Point<Arithmetic>> query(const Rectangle <Arithmetic> & area) noexcept {
			std::vector <Point<Arithmetic>> results;
			query(area, results);
			return results;
		}
		bool search(const Point <Arithmetic> & point) noexcept {
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
		void clear() noexcept {
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