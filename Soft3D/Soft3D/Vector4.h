#ifndef _Vector4_H__
#define _Vector4_H__

#include "DllApi.h"
#include "Types.h"

namespace Soft3D{

	class DLLAPI Vector4{
	public:
		Vector4();
		Vector4(Float x, Float y, Float z, Float w);
		Vector4* Clone();

		Vector4& Add(const Vector4& rhs);
		Vector4& Sub(const Vector4& rhs);
		Vector4& Mul(Float rhs);
		Vector4& Div(Float rhs);
	public:
		Float x;
		Float y;
		Float z;
		Float w;

	};

}

#endif