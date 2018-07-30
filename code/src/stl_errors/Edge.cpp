#include "Edge.h"

using namespace std;

namespace rk9
{
	bool EdgesVertice(const Edge& a, const Edge& b, Point& p) {
		if (a.A == b.A || a.A == b.B) {
			p = a.A;
			return true;
		}
		else if (a.B == b.A || a.B == b.B) {
			p = a.B;
			return true;
		}
		return false;
	}

	bool operator<(const Point& a, const Point& b) {
		if (a.X != b.X) {
			return a.X < b.X;
		}
		if (a.Y != b.Y) {
			return a.Y < b.Y;
		}
		return a.Z < b.Z;
	}

	bool Edge::operator<(const Edge& other) const{
		return centre() < other.centre();
	}

	unsigned GetEdgesCount(PolyModel model) {

		unsigned triangles_count = model.GetTrianglesCount();
		return triangles_count * 3;

	}
};

