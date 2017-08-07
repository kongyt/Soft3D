#ifndef _Quaternion_H__
#define _Quaternion_H__

#include "Types.h"
#include "MathUtils.h"
#include "Vector3.h"

namespace Soft3D {

	class Quaternion {
	public:
		Quaternion();
		Quaternion(Float x, Float y, Float z, Float w);
		Quaternion(Float yaw, Float pitch, Float roll);
		Quaternion* Clone();

		Float Dot(const Quaternion& rhs);
		Quaternion Lerp(const Quaternion& rhs, Float t);
		Quaternion Slerp(const Quaternion& rhs, Float t);
		Float Angle(const Quaternion& rhs);
		void SetEulerAngle(Float yaw, Float pitch, Float roll);
		void Set(Float x, Float y, Float z, Float w);
		Quaternion Conjugate();
		Quaternion Inverse();
		Vector3 EulerAngle();

	public:
		Float x;
		Float y;
		Float z;
		Float w;

	};

}

#endif