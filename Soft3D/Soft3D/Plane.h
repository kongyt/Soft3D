#ifndef _Plane_H__
#define _Plane_H__

#include "Vector3.h"

namespace Soft3D {
	
	enum PlaneSide {
		OnPlane,
		Back,
		Front
	};

	// AX + BY + CZ + D = 0
	// Vector3(A, B, C) is normal.
	// D is dis.
	class Plane {
	public:
		void Set(const Vector3& normal, Float dis);
		void Set(const Vector3& normal, const Vector3& point);
		void Set(const Vector3& p1, const Vector3& p2, const Vector3& p3);

		Float Dis(const Vector3& point);
		PlaneSide TestPoint(const Vector3& point);
		Bool IsFrontFacing(const Vector3& direction);
		Vector3 GetNormal();
		Float GetDis();

	public:
		Vector3 m_normal;   // The plane normal
		Float   m_dis;		// The distance to the origin
	};

}

#endif