#include "Plane.h"
#include "MathUtils.h"

namespace Soft3D {

	void Plane::Set(const Vector3& normal, Float dis) {
		m_normal.Set(normal).Nor();
		m_dis = dis;
	}

	void Plane::Set(const Vector3& normal, const Vector3& point) {
		m_normal.Set(normal);
		m_dis = -m_normal.Dot(point);
	}

	void Plane::Set(const Vector3& p1, const Vector3& p2, const Vector3& p3) {
		Vector3 l = Vector3().Add(p1).Sub(p2);
		Vector3 r = Vector3().Add(p2).Sub(p3);
		l.Crs(r).Nor();

		m_normal.Set(l);
		m_dis = -l.Dot(p1);
	}

	Float Plane::Dis(const Vector3& point) {
		return m_normal.Dot(point) + m_dis;
	}


	PlaneSide Plane::TestPoint(const Vector3& point) {
		Float dist = m_normal.Dot(point) + m_dis;

		if (MathUtils::IsZero(dist)) {
			return PlaneSide::OnPlane;
		}
		else if (dist < 0) {
			return PlaneSide::Back;
		}
		else {
			return PlaneSide::Front;
		}
	}


	Bool Plane::IsFrontFacing(const Vector3& direction) {
		return m_normal.Dot(direction) <= 0;
	}

	Vector3 Plane::GetNormal() {
		return m_normal;
	}


	Float Plane::GetDis() {
		return m_dis;
	}

}