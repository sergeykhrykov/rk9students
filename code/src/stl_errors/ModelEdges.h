#pragma once
#include <vector>

#include "Edge.h"


namespace rk9
{
	class ModelEdges {      //класс дл€ работы с вектором, содержащим рЄбра STL модели

		std::vector<Edge> Edges;      //вектор рЄбер STL модели

	public:

		void AddEdge(Point p1, Point p2);      //функци€ добавлени€ ребра в вектор

		void WriteEdges(PolyModel model);      //функци€ записи рЄбер STL модели в вектор

		vector<Edge> FindErrors(PolyModel model);      //функци€ нахождени€ ребер STL модели, составл€ющих дыры

		size_t CountOfHoles(vector<Edge> edges);

		bool SelfIntersection(Point p, vector<Point> points);

	};
}