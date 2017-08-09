#ifndef _Camera_H__
#define _Camera_H__

#include "Vector3.h"

namespace Soft3D {

	class Camera {
	public:
		Vector3 GetForwardVector();
		Vector3 GetUpVector();
		Vector3 GetOrigin();

	};

}

#endif

