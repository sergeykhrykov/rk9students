#include <algorithm>
#include <map>
#include <set>

#include "ModelEdges.h"


using namespace std;

namespace rk9
{
	void ModelEdges::AddEdge(Point p1, Point p2) {
		Edge e{ p1, p2 };
		Edges.push_back(e);
	}

	void ModelEdges::WriteEdges(PolyModel model) {

		unsigned edgescount = GetEdgesCount(model);

		for (unsigned i = 0; i < edgescount / 3; i++)
		{
			Triangle tr = model.GetTriangleVertices(i);
			if (tr.A < tr.B)
				AddEdge(tr.A, tr.B);
			else
				AddEdge(tr.B, tr.A);
			if (tr.B < tr.C)
				AddEdge(tr.B, tr.C);
			else
				AddEdge(tr.C, tr.B);
			if (tr.A < tr.C)
				AddEdge(tr.A, tr.C);
			else
				AddEdge(tr.C, tr.A);
		}
	}

	bool ModelEdges::SelfIntersection(Point p, vector<Point> points) {
		for (size_t i = 0; i < points.size(); i++)
			if (p == points[i])
				return true;
		return false;
	}

	size_t ModelEdges::CountOfHoles(vector<Edge> edges) {

		size_t holesCount = 0;

		vector<Point> points;

		Point p;

		Point p_cur;

		int flag = 0;

		while (edges.size() > 0) {
			Edge cur = edges[0];

			edges.erase(edges.begin());

			for (size_t i = 0; i < edges.size(); i++) {
				if (EdgesVertice(cur, edges[i], p)) {
					if (!(p == p_cur)) 
						if (SelfIntersection(p, points)) {
							holesCount++;
						}
						else {
							points.push_back(p);
							p_cur = p;
							cur = edges[i];
							edges.erase(edges.begin() + i);
							i = -1;
							flag++;
						}
				}
			}
			holesCount++;
			points.clear();
		}

		return holesCount;
	}

	vector<Edge> ModelEdges::FindErrors(PolyModel model) {      //нахождение ребер, составл€ющих дыры заключаетс€ в поиске ребер, не имеющих пары ("на ребре расположено меньше двух треугольников")

		WriteEdges(model);

		std::sort(Edges.begin(), Edges.end());  //оператор сравнени€ в виде л€мбда-функции

		map <Edge, size_t> edgesToCount;      //ассоциативный отсортированный контейнер, содержит 2 типа данных: Edge - ребро модели и Count - сколько раз это ребро встречаетс€ в модели

		vector <Edge> holeEdges;      //вектор ребер, составл€ющих дыры модели

		map <Edge, size_t> nonManifoldToCount;      //ассоциативный отсортированный контейнер non-manifold ребер модели

		for (const auto& e : Edges)      //range based for loop - цикл дл€ контейнеров. ќт begin до end
			++edgesToCount[e];

		for (const auto& pr : edgesToCount) {      //range based for loop - цикл дл€ контейнеров. ќт begin до end
			if (pr.second == 1)
				holeEdges.push_back(pr.first);
			else if (pr.second > 2)
				nonManifoldToCount.insert(pr);
		}

		size_t holesCount = 0;
		holesCount = CountOfHoles(holeEdges);

		return holeEdges;
	}
};