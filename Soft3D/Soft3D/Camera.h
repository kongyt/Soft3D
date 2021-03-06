#ifndef _Camera_H__
#define _Camera_H__

#include "DllApi.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Frustum.h"

namespace Soft3D {

	class DLLAPI Camera : public GameObject{
	public:
		void Update(Bool updateFrustum);
		void SetToOrth(Float viewportWidth, Float viewportHeight);
		void SetToOrth(Bool yDown, Float viewportWidth, Float viewportHeight);
		void SetToPers(Float fieldOfView, Float viewportWidth, Float viewportHeight);
		void Unproject(Vector3& vec, float viewportX, float viewportY, float viewportWidth, float viewportHeight);


	public:
		Vector3 m_direction = Vector3(0, 0, -1);
		Vector3 m_up = Vector3(0, 1, 0);

		Vector3 m_tmp;
		Matrix4 m_projection;
		Matrix4 m_view;
		Matrix4 m_combined;
		Matrix4 m_invProjectionView;

		Bool isOrth;

		Float m_zoom = 1.0f;
		Float m_near = 0.0f;
		Float m_far = 10000.0f;
		Float m_viewportWidth;
		Float m_viewportHeight;

		Float m_fieldOfView;
		
		Frustum m_frustum;
	};



}

#endif

