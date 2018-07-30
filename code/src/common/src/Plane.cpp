#include <algorithm>
#include <array>

#include "common/Plane.h"
#include "common/BoundingBox.h"

using namespace std;

namespace rk9 {

	bool Plane::GetIntersectionWithLine(Point point_1, Point point_2, Point& result) {

		double p1, p2, p3;

		p1 = point_2.X - point_1.X;
		p2 = point_2.Y - point_1.Y;
		p3 = point_2.Z - point_1.Z;

		double x1, y1, z1;

		x1 = point_1.X;
		y1 = point_1.Y;
		z1 = point_1.Z;

		// ѕроверка, что точка перечесени€ есть
		if (A*p1 + B*p2 + C*p3 == 0.0) {
			return false;
		}

		double t = -(A*x1 + B*y1 + C*z1 + D) / (A*p1 + B*p2 + C*p3);
		
		result.X = x1 + p1*t;
		result.Y = y1 + p2*t;
		result.Z = z1 + p3*t;

		return true;
	}

	bool IsValueBetween(double val, double a, double b){
		if (a < b)
			return (a <= val) && (val <= b); // [a; b]
		else
			return (b <= val) && (val <= a); // [b; a]
	}

	bool Plane::GetIntersectionWithLineSegment(Point point_1, Point point_2, Point & result)
	{
		Point p;
		if (GetIntersectionWithLine(point_1, point_2, p))
		{
			
			if (   (IsValueBetween(p.X, point_1.X, point_2.X))
				&& (IsValueBetween(p.Y, point_1.Y, point_2.Y))
				&& (IsValueBetween(p.Z, point_1.Z, point_2.Z))) 
			{
				result = p;
				return true;
			}
		}
		return false;
	}

	bool less(pair<double, unsigned> a, pair<double, unsigned> b) {
		return a.first < b.first;
	}

	//PolyModel Plane::GetPolyRepresentation(BoundingBox bbox)
	//{

	//	// ¬ершины ограничивающего параллелепипеда
	//	Point v[8];

	//	v[0].X = bbox.Xmax;  v[4].X = bbox.Xmax;
	//	v[0].Y = bbox.Ymin;  v[4].Y = bbox.Ymin;
	//	v[0].Z = bbox.Zmax;  v[4].Z = bbox.Zmin;

	//	v[1].X = bbox.Xmax;  v[5].X = bbox.Xmax;
	//	v[1].Y = bbox.Ymax;  v[5].Y = bbox.Ymax;
	//	v[1].Z = bbox.Zmax;  v[5].Z = bbox.Zmin;

	//	v[2].X = bbox.Xmin;  v[6].X = bbox.Xmin;
	//	v[2].Y = bbox.Ymax;  v[6].Y = bbox.Ymax;
	//	v[2].Z = bbox.Zmax;  v[6].Z = bbox.Zmin;

	//	v[3].X = bbox.Xmin;  v[7].X = bbox.Xmin;
	//	v[3].Y = bbox.Ymin;  v[7].Y = bbox.Ymin;
	//	v[3].Z = bbox.Zmax;  v[7].Z = bbox.Zmin;

	//	// –ебра 
	//			
	//	typedef std::pair<Point, Point> Edge;

	//	array<Edge, 12> e { {
	//		{ v[0], v[1] },
	//		{ v[1], v[2] },
	//		{ v[2], v[3] },
	//		{ v[3], v[0] },

	//		{ v[0], v[4] },
	//		{ v[1], v[5] },
	//		{ v[2], v[6] },
	//		{ v[3], v[7] },

	//		{ v[4], v[5] },
	//		{ v[5], v[6] },
	//		{ v[6], v[7] },
	//		{ v[7], v[4] }
	//	} };

	//	// “очки пересечени€ плоскости с ребрами
	//	vector<Point> intersect_pts;

	//	for (auto edge : e) {
	//		Point p;
	//		if (GetIntersectionWithLineSegment(edge.first, edge.second, p)) {
	//			intersect_pts.push_back(p);
	//		}
	//	}

	//	unsigned intersect_pts_count = intersect_pts.size();

	//	PolyModel model;

	//	if (intersect_pts_count == 0)
	//	{
	//		return model;
	//	}

	//	// ћассив углов между вектором на точку 
	//	// и векторами на остальные точки фигуры пересечени€
	//	vector<pair<double, unsigned>> angles(intersect_pts.size());
	//	
	//	// angles[i] - это угол между 1-м и i-м векторами

	//	angles[1] = make_pair(0.0, 1);

	//	double max_angle = 0.0;
	//	size_t max_angle_index = 0;

	//	for (size_t i = 2; i < intersect_pts_count; ++i)
	//	{
	//		double angle = GetAngleBetweenVectors(intersect_pts[0],
	//			intersect_pts[1],
	//			intersect_pts[i]);

	//		angles[i] = make_pair(angle, i);

	//		if (max_angle < angle) {
	//			max_angle = angle;
	//			max_angle_index = i;
	//		}
	//	}

	//	for (size_t i = 1; i < intersect_pts_count; ++i)
	//	{
	//		double angle = GetAngleBetweenVectors(intersect_pts[0],
	//			intersect_pts[max_angle_index],
	//			intersect_pts[i]);

	//		if (i == max_angle_index) { angle = 0.0; };

	//		angles[i] = make_pair(angle, i);
	//	}

	//	sort(angles.begin() + 1, angles.end(), less);

	//	// —троим треугольники и добавл€ем их в модель
	//	for (unsigned i = 2; i < intersect_pts_count; ++i)
	//	{
	//		Point p1 = intersect_pts[0];
	//		Point p2 = intersect_pts[angles[i-1].second];
	//		Point p3 = intersect_pts[angles[i].second];
	//		model.AddTriangle(p1, p2, p3);
	//	}

	//	return model;
	//}

}