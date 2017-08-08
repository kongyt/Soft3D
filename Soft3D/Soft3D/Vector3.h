#ifndef _Vector3_H__
#define _Vector3_H__

#include "DllApi.h"
#include "Types.h"

namespace Soft3D {

	class DLLAPI Vector3 {
	public:
		Vector3();
		Vector3(Float x, Float y, Float z);
		Vector3* Clone();

		Vector3& Add(const Vector3& rhs);
		Vector3& Sub(const Vector3& rhs);
		Vector3& Mul(Float rhs);
		Vector3& Div(Float rhs);

	public:
		Float x;
		Float y;
		Float z;

	};

}

#endif