#include "Frustum.h"
#include "MathUtils.h"

namespace Soft3D {

	void Frustum::Update(const Matrix4& inverseProjectionView) {
		
	}

	Bool Frustum::PointInFrustum(const Vector3& point) {
		for (int i = 0; i < 6; i++) {
			PlaneSide result = planes[i].TestPoint(point);
			if (result == PlaneSide::Back) {
				return false;
			}
		}
		return true;
	}

	Bool Frustum::SphereInFrustum(const Vector3& center, Float radius) {
		for (int i = 0; i < 6; i++) {
			if (planes[i].m_normal.x * center.x + planes[i].m_normal.y * center.y + planes[i].m_normal.z * center.z < (-radius - planes[i].m_dis)) {
				return false;
			}
		}
		return true;
	}

	Bool Frustum::SphereInFrustumWithoutNearFar(const Vector3& center, Float radius) {
		for (int i = 2; i < 6; i++) {
			if (planes[i].m_normal.x * center.x + planes[i].m_normal.y * center.y + planes[i].m_normal.z * center.z < (-radius - planes[i].m_dis)) {
				return false;
			}
		}
		return true;
	}

}