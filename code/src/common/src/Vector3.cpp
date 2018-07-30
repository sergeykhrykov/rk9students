#include "common/Vector3.h"

namespace rk9
{

	Vector3 Vector3::CrossProduct(Vector3 v1, Vector3 v2){
		return Vector3{
						 v1.B * v2.C - v2.B * v1.C,
						-v1.A * v2.C + v2.A * v1.C,
						 v1.A * v2.B - v2.A * v1.B
					  };
	}

	double Vector3::DotProduct(Vector3 v1, Vector3 v2) {
		return v1.A * v2.A + v1.B*v2.B + v1.C*v2.C;
	}

	double Vector3::GetAngleBetweenVectors(Vector3 v1, Vector3 v2)
	{
		return acos(
				Vector3::DotProduct(v1, v2)	/
				( v1.GetLength() * v2.GetLength() )
			   );
	}

	bool operator==(const Vector3& v1, const Vector3& v2) {
		return v1.A == v2.A && v1.B == v2.B && v1.C == v2.C;
	}

}