#ifndef _Vector2_H__
#define _Vector2_H__

#include "DllApi.h"
#include "Types.h"

namespace Soft3D{

	class DLLAPI Vector2 {
	public:
		Vector2();
		Vector2(Float x, Float y);

	public:
		Float x;
		Float y;
	};

}

#endif