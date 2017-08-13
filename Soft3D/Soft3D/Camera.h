#ifndef _Camera_H__
#define _Camera_H__

#include "DllApi.h"
#include "RenderSystemInterface.h"
#include "Vector3.h"
#include "GObj.h"
#include "Frustum.h"

namespace Soft3D {

	class DLLAPI Camera : public GObj{
	public:
		void Update(Bool updateFrustum);
		void Apply(RenderSystemInterface* renderSystem);
		void SetToOrth(Float viewportWidth, Float viewportHeight);
		void SetToOrth(Bool yDown, Float viewportWidth, Float viewportHeight);
		void SetToPers(Float fieldOfView, Float viewportWidth, Float viewportHeight);



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
		Float m_far = 1000.0f;
		Float m_viewportWidth;
		Float m_viewportHeight;

		Float m_fieldOfView;
		
		Frustum m_frustum;

		RenderSystemInterface* m_renderSystem;

	};



}

#endif

