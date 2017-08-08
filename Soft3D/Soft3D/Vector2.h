#ifndef _Vector2_H__
#define _Vector2_H__

#include "DllApi.h"
#include "Types.h"

namespace Soft3D {

	class DLLAPI Vector2 {
	public:
		Vector2();
		Vector2(Float x, Float y);
		Vector2* Clone();

		Vector2& Add(const Vector2& rhs);
		Vector2& Sub(const Vector2& rhs);
		Vector2& Mul(Float rhs);
		Vector2& Div(Float rhs);


	public:
		Float x;
		Float y;

	};

}

#endif