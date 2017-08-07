#ifndef _Vector3_H__
#define _Vector3_H__

#include "Types.h"

namespace Soft3D {

	class Vector3 {
	public:
		Vector3();
		Vector3(Float a, Float b, Float c);
		Vector3* Clone();

		Vector3& Add(const Vector3& rhs);
		Vector3& Sub(const Vector3& rhs);
		Vector3& Mul(Float rhs);
		Vector3& Div(Float rhs);

	public:
		Float a;
		Float b;
		Float c;

	};

}

#endif