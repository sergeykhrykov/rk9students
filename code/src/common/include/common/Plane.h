#pragma once

#include "BoundingBox.h"
#include "Point.h"

#include "common/common_api.h"

namespace rk9
{
	struct COMMON_API Plane {

		// ��������� ��������� Ax + By + Cz + D = 0
		double A, B, C, D;
		
		Plane() :
			A(1.0),
			B(0.0),
			C(0.0),
			D(0.0) {};

		Plane(double a, double b, double c, double d) :
			A(a),
			B(b),
			C(c),
			D(d) {};

		// �������� ������������� ��������� � ���� ��������������,
		// ������������� ������ Bounding Box'��
		// PolyModel GetPolyRepresentation(BoundingBox bbox);

		// �������� ���������� ����� ����������� ��������� � ������.
		// point_1, point_2 - �����, ����� ������� �������� �������� ������;
		// result - ������� ����� �����������
		// ���������� true, ����������� �������. � ��������� ������ ���������� false
		bool GetIntersectionWithLine(Point point_1, Point point_2, Point& result);


		// �������� ���������� ����� ����������� ��������� � ��������.
		// point_1, point_2 - ������� �������;
		// result - ������� ����� �����������
		// ���������� true, ����������� �������. � ��������� ������ ���������� false
		// ���� ����� ����������� ����, ��� ����������� ����������� �������.
		bool GetIntersectionWithLineSegment(Point point_1, Point point_2, Point& result);
	};
}