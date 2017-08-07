#ifndef _Math_Utils_H__
#define _Math_Utils_H__

#include <math.h>

#include "Types.h"

namespace Soft3D {

	class MathUtils {
	public:
		static Float Epsilon();		
		static Float Pi();
		static Bool  IsZero(Float val);
		static Float Rad2Deg(Float radian);
		static Float Min(Float v1, Float v2);
		static Float Max(Float v1, Float v2);
		static Float Clamp(Float value, Float v1, Float v2);
		static Float Abs(Float val);

	};

}


#endif