#ifndef _Math_Utils_H__
#define _Math_Utils_H__

#include <math.h>
#include "DllApi.h"
#include "Types.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

namespace Soft3D {	

	class DLLAPI MathUtils {
	public:
		static Float Epsilon();		
		static Float Pi();
		static Bool  IsZero(Float val);
		static Bool  IsEqual(Float val1, Float val2);
		static Float Rad2Deg(Float radian);
		static Float Min(Float v1, Float v2);
		static Float Max(Float v1, Float v2);
		static Float Clamp(Float value, Float v1, Float v2);
		static Float Abs(Float val);
		static Float Distance(const Vector3& point, const Vector4& plane);
		static void TransformVector4(Vector4& out, const Vector4& vec4, const Matrix4& mat);
		static void CrossProduct3(Vector3& out, const Vector3& u, const Vector3& v);
		static void GetPointEquation(Vector4& out, const Vector3& p1, const Vector3& p2, const Vector3& p3);
	};

}


#endif