#include "Frustum.h"
#include "MathUtils.h"

namespace Soft3D {

	void Frustum::Update(Matrix4& inverseProjectionView) {
		
		for (int i = 0; i < 8; i++) {
			inverseProjectionView.Prj(planePoints[i]);
		}		

		planes[0].Set(planePoints[1], planePoints[0], planePoints[2]);
		planes[1].Set(planePoints[4], planePoints[5], planePoints[7]);
		planes[2].Set(planePoints[0], planePoints[4], planePoints[3]);
		planes[3].Set(planePoints[5], planePoints[1], planePoints[6]);
		planes[4].Set(planePoints[2], planePoints[3], planePoints[6]);
		planes[5].Set(planePoints[4], planePoints[0], planePoints[1]);
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