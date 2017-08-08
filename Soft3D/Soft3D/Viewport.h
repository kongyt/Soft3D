#ifndef _Viewport_H__
#define _Viewport_H__

#include "DllApi.h"
#include "Types.h"

namespace Soft3D {

	class DLLAPI Viewport {
	public:
		Viewport(Int width, Int height);
		Viewport(Int x, Int y, Int width, Int height);

	public:
		Int x = 0;
		Int y = 0;
		Int width = 0;
		Int height = 0;
	};

}

#endif