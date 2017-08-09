#ifndef _Frustum_H__
#define _Frustum_H__

#include "Vector3.h"
#include "Matrix4.h"
#include "Vector4.h"
#include "Camera.h"

namespace Soft3D {

	//  ”æ∞ÃÂ
	class Frustum {
	public:
		void SetOrthographic(Float xMin, Float xMax, Float yMin, Float yMax, Float zMin, Float zMax);
		void SetPerspective(Float fov, Float aspect, Float near, Float far);
		void Transform(Camera& camera);
		Bool TestSphere(Float x, Float y, Float z, Float radius);
		Bool TestSphere(const Vector3& point, Float radius);

		const Matrix4& GetProjectionMatrix();

	public:

		// projection matrix for frustum
		Matrix4 projectionMatrix;

		// untransformed corners of the frustum
		Vector4 nearUL, nearLL, nearUR, nearLR;
		Vector4 farUL, farLL, farUR, farLR;
		
		// transformed corners of frustum
		Vector4 nearULT, nearLLT, nearURT, nearLRT;
		Vector4 farULT, farLLT, farURT, farLRT;

		// base and transformed plane equations
		Vector4 nearPlane, farPlane, leftPlane, rightPlane, topPlane, bottomPlane;

	};

}

#endif