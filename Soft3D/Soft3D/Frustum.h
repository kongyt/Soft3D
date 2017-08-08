#ifndef _Frustum_H__
#define _Frustum_H__

#include "../Soft3D/Vector3.h"

namespace Soft3D {

	class Frustum {

	public:
		const static Vector3 nearUL;	// near upper left
		const static Vector3 nearLL;    // near lower left
		const static Vector3 nearUR;    // near upper right
		const static Vector3 nearLR;    // near lower right
		const static Vector3 farUL;     // far  upper left
		const static Vector3 farLL;     // far  lower left
		const static Vector3 farUR;     // far  upper right
		const static Vector3 farLR;     // far  lower right

	};

}

#endif