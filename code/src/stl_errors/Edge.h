#pragma once
#include <vector>

#include "common/Plane.h"
#include "common/Point.h"
#include "common/PolyModel.h"
#include "common/Triangle.h"
#include "common/Vector3.h"

using namespace std;

namespace rk9
{
	bool operator<(const Point& a, const Point& b);

	struct Edge {      //структура ребра STL модели

		Point Verts[2];

		Point &A = Verts[0],
			&B = Verts[1];

		Edge() {}

		~Edge() {}

		Edge(const Edge& t) {
			Verts[0] = t.Verts[0];
			Verts[1] = t.Verts[1];
		}
		Edge& operator=(const Edge& other) {
			Verts[0] = other.Verts[0];
			Verts[1] = other.Verts[1];
			return *this;
		}

		bool operator==(const Edge& other) {
			return this->A == other.A &&
				   this->B == other.B;
		}

		Point centre() const {
			return Point((A.X + B.X) / 2.0, (A.Y + B.Y) / 2.0, (A.Z + B.Z) / 2.0);
		}

		bool operator<(const Edge& other) const;

		Edge(Point p1, Point p2) {
			Verts[0] = p1;
			Verts[1] = p2;
		};
	};

	unsigned GetEdgesCount(PolyModel model);     //количество ребер в STL модели

	bool EdgesVertice(const Edge& a, const Edge& b, Point& p);

}

