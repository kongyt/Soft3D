#ifndef _Frustum_H__
#define _Frustum_H__

#include "DllApi.h"
#include "Types.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Plane.h"

namespace Soft3D {

	//  ”æ∞ÃÂ
	class DLLAPI Frustum {
	public:
		void Update(const Matrix4& inverseProjectionView);
		Bool PointInFrustum(const Vector3& point);
		Bool SphereInFrustum(const Vector3& center, Float radis);
		Bool SphereInFrustumWithoutNearFar(const Vector3& center, Float radius);
		

	public:
		Vector3 planePoints[8];
		Plane planes[6];
	};

}

#endif