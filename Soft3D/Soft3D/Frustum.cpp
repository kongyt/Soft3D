#include "Frustum.h"

namespace Soft3D {
	                                                                  // z    y     x
	const Vector3 Frustum::nearUL = Vector3(-1.0f,  1.0f, -1.0f);	  // near upper left
	const Vector3 Frustum::nearLL = Vector3(-1.0f, -1.0f, -1.0f);     // near lower left
	const Vector3 Frustum::nearUR = Vector3( 1.0f,  1.0f, -1.0f);     // near upper right
	const Vector3 Frustum::nearLR = Vector3( 1.0f, -1.0f, -1.0f);     // near lower right
	const Vector3 Frustum::farUL  = Vector3(-1.0f,  1.0f,  1.0f);     // far  upper left
	const Vector3 Frustum::farLL  = Vector3(-1.0f, -1.0f,  1.0f);     // far  lower left
	const Vector3 Frustum::farUR  = Vector3( 1.0f,  1.0f,  1.0f);     // far  upper right
	const Vector3 Frustum::farLR  = Vector3( 1.0f, -1.0f,  1.0f);     // far  lower right

}