//Include M_PI constant
#define _USE_MATH_DEFINES
#include <math.h>

#include <cmath>
#include "gtest/gtest.h"
#include "common/Plane.h"
#include "common/Vector3.h"
#include "common/Triangle.h"

using namespace std;
using namespace rk9;

TEST(PlaneTest, GetIntersectionWithLineTest) {
	Plane p{ 1, 0, 0, 0 }; // x=0
	Point res;

	EXPECT_TRUE(
		p.GetIntersectionWithLine(Point{ -10, 0, 0 }, 
			Point{ 10, 0, 0 }, 
			res));

	Point eq{ 0, 0, 0 };

	EXPECT_EQ(res, eq);

	EXPECT_FALSE(
		p.GetIntersectionWithLine(Point{ -10, 0, 0 },
			Point{ -10, 50, 0 },
			res));
}

TEST(Vector3Test, CrossProductTest) {
	Vector3 v1{ 1, 0, 0 }, 
			v2{ 0, 1, 0 },
			v3{ 0, 0, 1 };

	Vector3 product = Vector3::CrossProduct(v1, v2);

	EXPECT_EQ(product, v3);

	Vector3 v4{ 10, 0, 0 },
		v5{ 10, 10, 0 };

	double angle = Vector3::GetAngleBetweenVectors(v4, v5);

	EXPECT_DOUBLE_EQ(abs(sin(angle))*v4.GetLength()*v5.GetLength(),
		Vector3::CrossProduct(v4, v5).GetLength());
}

TEST(Vector3Test, GetAngleBetweenVectorsTest) {
	Vector3 v1{ 1, 0, 0 },
			v2{ 0, 1, 0 };
			
	double angle = Vector3::GetAngleBetweenVectors(v1, v2);

	EXPECT_DOUBLE_EQ(angle, M_PI/2.0);
}

TEST(Vector3Test, DotProductTest) {
	Vector3 v1{ 1, 0, 0 },
			v2{ 0, 1, 0 },
			v3{ 264.5, 0, -748.6 }; // Произвольный вектор

	EXPECT_DOUBLE_EQ(Vector3::DotProduct(v1, v2), 0.0);

	// Скалярное произведение всегда неотрицательно
	EXPECT_TRUE(Vector3::DotProduct(v1, v3) >= 0.0);
}


TEST(TriangleTest, GetAreaTest) {

	// Треугольник, лежащий в плоскости OXY
	Triangle t1{ Point{ 0, 0, 0 }, Point{ 0, 10, 0 }, Point{ 10, 0, 0 } };
	Triangle t2{ Point{ 0, 0, 0 }, Point{ 0, 0, 0 }, Point{ 0, 0, 0 } };
	Triangle t3{ Point{ 0, 0, 0 }, Point{ 0, 0, 10 }, Point{ 0, 10, 10 } };

	EXPECT_DOUBLE_EQ(t1.GetArea(), 50.0);
	EXPECT_DOUBLE_EQ(t2.GetArea(), 0.0);
	EXPECT_DOUBLE_EQ(t3.GetArea(), 50.0);
}

TEST(TriangleTest, IsPointInsideTriangleTest) {
	
	// Треугольник, лежащий в плоскости OXY
	Triangle t{ Point{0, 0, 0}, Point{0, 10, 0}, Point{10, 0, 0} };

	Point p{ 1, 1, 0 };

	EXPECT_TRUE(t.IsPointInsideTriangle(p));
}
