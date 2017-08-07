#ifndef _Vector2_H__
#define _Vector2_H__

#include "Types.h"

namespace Soft3D {

	class Vector2 {
	public:
		Vector2();
		Vector2(Float a, Float b);
		Vector2* Clone();

		Vector2& Add(const Vector2& rhs);
		Vector2& Sub(const Vector2& rhs);
		Vector2& Mul(Float rhs);
		Vector2& Div(Float rhs);


	public:
		Float a;
		Float b;

	};

}

#endif