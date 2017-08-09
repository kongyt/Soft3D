#include "Frustum.h"
#include "MathUtils.h"

namespace Soft3D {

	void Frustum::SetOrthographic(Float xMin, Float xMax, Float yMin, Float yMax, Float zMin, Float zMax) {
		projectionMatrix.Identity();

		projectionMatrix.data[M00] = 2.0f / (xMax - xMin);
		projectionMatrix.data[M11] = 2.0f / (yMax - yMin);
		projectionMatrix.data[M22] = -2.0f / (zMax - zMin);
		projectionMatrix.data[M03] = -((xMax + xMin) / (xMax - xMin));
		projectionMatrix.data[M13] = -((yMax + yMin) / (yMax - yMin));
		projectionMatrix.data[M23] = -((zMax + zMin) / (zMax - zMin));
		projectionMatrix.data[M33] = 1.0f;

		// Fill in values for untransformed Frustum corners
		// Near Upper Left
		nearUL.x = xMin; nearUL.y = yMax; nearUL.z = zMin; nearUL.w = 1.0f;

		// Near Lower Left
		nearLL.x = xMin; nearLL.y = yMin; nearLL.z = zMin; nearLL.w = 1.0f;

		// Near Upper Right
		nearUR.x = xMax; nearUR.y = yMax; nearUR.z = zMin; nearUR.w = 1.0f;

		// Near Lower Right
		nearLR.x = xMax; nearLR.y = yMin; nearLR.z = zMin; nearLR.w = 1.0f;

		// Far Upper Left
		farUL.x = xMin; farUL.y = yMax; farUL.z = zMax; farUL.w = 1.0f;

		// Far Lower Left
		farLL.x = xMin; farLL.y = yMin; farLL.z = zMax; farLL.w = 1.0f;

		// Far Upper Right
		farUR.x = xMax; farUR.y = yMax; farUR.z = zMax; farUR.w = 1.0f;

		// Far Lower Right
		farLR.x = xMax; farLR.y = yMin; farLR.z = zMax; farLR.w = 1.0f;

	}

	void Frustum::SetPerspective(Float fov, Float aspect, Float near, Float far) {
		Float xmin, xmax, ymin, ymax;       // Dimensions of near clipping plane
		Float xFmin, xFmax, yFmin, yFmax;   // Dimensions of far clipping plane

											// Do the Math for the near clipping plane
		ymax = near * float(tan(fov * MathUtils::Pi() / 360.0));
		ymin = -ymax;
		xmin = ymin * aspect;
		xmax = -xmin;

		projectionMatrix.Identity();
		projectionMatrix.data[M00] = (2.0f * near) / (xmax - xmin);
		projectionMatrix.data[M11] = (2.0f * near) / (ymax - ymin);
		projectionMatrix.data[M02] = (xmax + xmin) / (xmax - xmin);
		projectionMatrix.data[M12] = (ymax + ymin) / (ymax - ymin);
		projectionMatrix.data[M22] = -((far + near) / (far - near));
		projectionMatrix.data[M23] = -1.0f;
		projectionMatrix.data[M32] = -((2.0f * far * near) / (far - near));
		projectionMatrix.data[M33] = 0.0f;

		// Do the Math for the far clipping plane
		yFmax = far * float(tan(fov * MathUtils::Pi() / 360.0));
		yFmin = -yFmax;
		xFmin = yFmin * aspect;
		xFmax = -xFmin;


		// Fill in values for untransformed Frustum corners
		// Near Upper Left
		nearUL.x = xmin; nearUL.y = ymax; nearUL.z = -near; nearUL.w = 1.0f;

		// Near Lower Left
		nearLL.x = xmin; nearLL.y = ymin; nearLL.z = -near; nearLL.w = 1.0f;

		// Near Upper Right
		nearUR.x = xmax; nearUR.y = ymax; nearUR.z = -near; nearUR.w = 1.0f;

		// Near Lower Right
		nearLR.x = xmax; nearLR.y = ymin; nearLR.z = -near; nearLR.w = 1.0f;

		// Far Upper Left
		farUL.x = xFmin; farUL.y = yFmax; farUL.z = -far; farUL.w = 1.0f;

		// Far Lower Left
		farLL.x = xFmin; farLL.y = yFmin; farLL.z = -far; farLL.w = 1.0f;

		// Far Upper Right
		farUR.x = xFmax; farUR.y = yFmax; farUR.z = -far; farUR.w = 1.0f;

		// Far Lower Right
		farLR.x = xFmax; farLR.y = yFmin; farLR.z = -far; farLR.w = 1.0f;
	}

	void Frustum::Transform(Camera& camera) {
		Matrix4 rotMat;
		Vector3 forward = camera.GetForwardVector();
		Vector3 up = camera.GetUpVector();
		Vector3 origin = camera.GetOrigin();
		Vector3 cross;
		
		MathUtils::CrossProduct3(cross, up, forward);

		rotMat.data[M00] = cross.x;
		rotMat.data[M10] = cross.y;
		rotMat.data[M20] = cross.z;
		rotMat.data[M30] = 0.0f;

		rotMat.data[M01] = up.x;
		rotMat.data[M11] = up.y;
		rotMat.data[M21] = up.z;
		rotMat.data[M31] = 0.0f;

		rotMat.data[M02] = forward.x;
		rotMat.data[M12] = forward.y;
		rotMat.data[M22] = forward.z;
		rotMat.data[M32] = 0.0f;

		rotMat.data[M03] = origin.x;
		rotMat.data[M13] = origin.y;
		rotMat.data[M23] = origin.z;
		rotMat.data[M33] = 1.0f;

		MathUtils::TransformVector4(nearULT, nearUL, rotMat);
		MathUtils::TransformVector4(nearLLT, nearLL, rotMat);
		MathUtils::TransformVector4(nearURT, nearUR, rotMat);
		MathUtils::TransformVector4(nearLRT, nearLR, rotMat);
		MathUtils::TransformVector4(farULT, farUL, rotMat);
		MathUtils::TransformVector4(farLLT, farLL, rotMat);
		MathUtils::TransformVector4(farURT, farUR, rotMat);
		MathUtils::TransformVector4(farLRT, farLR, rotMat);



	}

	Bool Frustum::TestSphere(Float x, Float y, Float z, Float radius) {
		return TestSphere(Vector3(x, y, z), radius);
	}

	Bool Frustum::TestSphere(const Vector3& point, Float radius) {
		Float dist;
		dist = MathUtils::Distance(point, nearPlane);
		if (dist + radius <= 0.0f) {
			return false;
		}

		dist = MathUtils::Distance(point, farPlane);
		if (dist + radius <= 0.0f) {
			return false;
		}

		dist = MathUtils::Distance(point, leftPlane);
		if (dist + radius <= 0.0f) {
			return false;
		}

		dist = MathUtils::Distance(point, rightPlane);
		if (dist + radius <= 0.0f) {
			return false;
		}

		dist = MathUtils::Distance(point, bottomPlane);
		if (dist + radius <= 0.0f) {
			return false;
		}

		dist = MathUtils::Distance(point, topPlane);
		if (dist + radius <= 0.0f) {
			return false;
		}

		return true;
	}

	const Matrix4& Frustum::GetProjectionMatrix() {
		return projectionMatrix;
	}

}