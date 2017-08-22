#include "Camera.h"

namespace Soft3D {

	void Camera::Update(Bool updateFrustum) {
		if (isOrth) {
			m_projection.SetToOrtho(m_zoom * -(m_viewportWidth / 2.0f), m_zoom * (m_viewportWidth / 2), m_zoom * -(m_viewportHeight / 2.0f),
				m_zoom * (m_viewportHeight / 2.0f), m_near, m_far);		
		}
		else {
			Float aspect = m_viewportWidth / m_viewportHeight;
			m_projection.SetToProjection(abs(m_near), abs(m_far), m_fieldOfView, aspect);
		}

		m_view.SetToLookAt(position, m_tmp.Set(position).Add(m_direction), m_up);
		m_combined.Set(m_projection).Mul(m_view);

		if (updateFrustum) {
			m_invProjectionView.Set(m_combined);
			m_invProjectionView.Inverse();
			m_frustum.Update(m_invProjectionView);
		}
	}

	void Camera::SetToOrth(Float viewportWidth, Float viewportHeight) {
		SetToOrth(false, viewportWidth, viewportHeight);
	}

	void Camera::SetToOrth(Bool yDown, Float viewportWidth, Float viewportHeight) {
		this->isOrth = true;
		if (yDown) {
			m_up.Set(0, -1, 0);
			m_direction.Set(0, 0, 1);
		}
		else {
			m_up.Set(0, 1, 0);
			m_direction.Set(0, 0, -1);
		}

		position.Set(m_zoom * viewportWidth / 2.0f, m_zoom * viewportHeight / 2.0f, 0);
		this->m_viewportWidth = viewportWidth;
		this->m_viewportHeight = viewportHeight;

		Update(true);
	}

	void Camera::SetToPers(Float fieldOfView, Float viewportWidth, Float viewportHeight) {
		this->m_fieldOfView = fieldOfView;
		this->m_viewportWidth = viewportWidth;
		this->m_viewportHeight = viewportHeight;

		Update(true);
	}

	void Camera::Unproject(Vector3& vec, float viewportX, float viewportY, float viewportWidth, float viewportHeight) {
		float x = vec.x, y = vec.y;
		x = x - viewportX;
		y = y - viewportY;
		vec.x = (2 * x) / viewportWidth - 1;
		vec.y = (2 * y) / viewportHeight - 1;
		vec.z = 2 * vec.z - 1;
		m_invProjectionView.Prj(vec);
	}

}