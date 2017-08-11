#ifndef _Vector3_H__
#define _Vector3_H__

#include "DllApi.h"
#include "Types.h"

namespace Soft3D {

	class Matrix4;

	class DLLAPI Vector3 {
	public:
		Vector3();
		Vector3(Float x, Float y, Float z);
		Vector3* Clone();		// return a copy of vector3.

		Vector3& Set(const Vector3& vec);
		Vector3& Set(Float x, Float y, Float z);

		Vector3& Add(const Vector3& vec);
		Vector3& Add(Float v1, Float v2, Float v3);

		Vector3& Sub(const Vector3& vec);
		Vector3& Sub(Float v1, Float v2, Float v3);

		Vector3& Scl(Float scalar);
		Vector3& Scl(Float scalarX, Float scalarY, Float scalarZ);

		Vector3& Nor();         // normalize vector3
		Float Dot(const Vector3& vec);   // dot product
		Vector3& Crs(const Vector3& vec);   // cross product

		Vector3& Mul(const Matrix4& mat);   // 
		Vector3& Prj(const Matrix4& mat);   // projection transform

		Vector3& Lerp(const Vector3& target, float t); 
		Vector3& Limit(Float limit);
		Vector3& Clamp(Float min, Float max);

		Float Len2();
		Float Len();

		Bool  Equal(const Vector3& vec);

		Float Dst2(const Vector3& vec);
		Float Dst(const Vector3& vec);

	public:
		Float x;
		Float y;
		Float z;

	};

}

#endif