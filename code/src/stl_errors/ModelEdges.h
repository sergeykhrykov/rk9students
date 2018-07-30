#pragma once
#include <vector>

#include "Edge.h"


namespace rk9
{
	class ModelEdges {      //����� ��� ������ � ��������, ���������� ���� STL ������

		std::vector<Edge> Edges;      //������ ���� STL ������

	public:

		void AddEdge(Point p1, Point p2);      //������� ���������� ����� � ������

		void WriteEdges(PolyModel model);      //������� ������ ���� STL ������ � ������

		vector<Edge> FindErrors(PolyModel model);      //������� ���������� ����� STL ������, ������������ ����

		size_t CountOfHoles(vector<Edge> edges);

		bool SelfIntersection(Point p, vector<Point> points);

	};
}