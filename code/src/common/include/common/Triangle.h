#pragma once

#include "common/common_api.h"

#include <cmath>

#include "Plane.h"
#include "Point.h"
#include "Vector3.h"

namespace rk9
{
	struct COMMON_API Triangle {
		
		Point Verts[3];

		// Ссылки для упрощения записи
	    Point &A = Verts[0], 
			  &B = Verts[1], 
			  &C = Verts[2];

		Triangle() {}

		~Triangle() {}

		Triangle(const Triangle& t) {
			Verts[0] = t.Verts[0];
			Verts[1] = t.Verts[1];
			Verts[2] = t.Verts[2];
		}

		Triangle& operator=(const Triangle& other) {
			Verts[0] = other.Verts[0];
			Verts[1] = other.Verts[1];
			Verts[2] = other.Verts[2];
			return *this;
		}

		Triangle(Point p1, Point p2, Point p3) {
			Verts[0] = p1;
			Verts[1] = p2;
			Verts[2] = p3;
		}

		// Вычислить площадь треугольника 
		double GetArea(){
			// S = 1/2 |AB x AC|
			return Vector3::CrossProduct(Vector3{ A, B }, 
										 Vector3{ A, C })
				   .GetLength() / 2.0;
		}

		// Вычислить нормаль к треугольнику
		Vector3 GetNormal();

		// Вычислить параметры уравнения плоскости, в кот. лежит треугольник
		Plane GetPlane();

		// Проверка, лежит ли данная точка внутри треугольника
		bool IsPointInsideTriangle(Point p);
	};
}