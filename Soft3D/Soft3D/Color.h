#ifndef _Color_H__
#define _Color_H__

#include "Types.h"
#include "MathUtils.h"

namespace Soft3D{

	class Color{
	public:
		Color();
		Color(Float r, Float g, Float b, Float a);
		Color(UInt color);
		Color* Clone();

		UInt ToUint();

	public:
		Float	r;
		Float	g;
		Float	b;
		Float	a;

	};

}

#endif