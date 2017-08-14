#ifndef _Matrix4_H__
#define _Matrix4_H__

#include <string.h>
#include <math.h>

#include "DllApi.h"
#include "Types.h"

#define M00		0
#define M10		1
#define M20		2
#define M30		3
#define M01		4
#define M11		5
#define M21		6
#define M31		7
#define M02		8
#define M12		9
#define M22		10
#define M32		11
#define M03		12
#define M13		13
#define M23		14
#define M33		15

namespace Soft3D {

	class Vector3;

	class DLLAPI Matrix4 {
	public:
		Matrix4();

		Matrix4* Clone();	

		Matrix4& Set(Float data[16]);
		Matrix4& Set(const Matrix4& mat4);

		Matrix4& Add(const Matrix4& mat4);
		Matrix4& Sub(const Matrix4& mat4);
		Matrix4& Mul(const Matrix4& mat4);

		Matrix4& Identity();
		Double Det();
		Matrix4& Inverse();
		Matrix4& Transpose();

		Matrix4& SetScale(const Vector3& scale);
		Matrix4& SetTranslate(const Vector3& trans);

		Matrix4& Scale(const Vector3& scale);
		Matrix4& Translate(const Vector3& trans);
		Matrix4& RotateX(Float rotation);
		Matrix4& RotateY(Float rotation);
		Matrix4& RotateZ(Float rotation);

		void Prj(Vector3& point);

		Matrix4& SetToProjection(Float near, Float far, Float fov, Float aspect);
		Matrix4& SetToOrtho2D(Float x, Float y, Float width, Float height);
		Matrix4& SetToOrtho2D(Float x, Float y, Float width, Float height, Float near, Float far);
		Matrix4& SetToOrtho(Float left, Float right, Float bottom, Float top, Float near, Float far);

		Matrix4& SetToLookAt(const Vector3& direction, const Vector3& up);
		Matrix4& SetToLookAt(const Vector3& position, const Vector3& target, const Vector3& up);

		Matrix4& SetToTranslation(const Vector3& vector);

	public:
		Float data[16];

	};

}

#endif