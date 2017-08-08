#ifndef _Matrix4_H__
#define _Matrix4_H__

#include <string.h>
#include <math.h>

#include "DllApi.h"
#include "Types.h"
#include "MathUtils.h"
#include "Vector3.h"

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

	class DLLAPI Matrix4 {
	public:
		Matrix4();
		Matrix4(Float data[16]);
		Matrix4* Clone();	

		Matrix4& CopyData(const Matrix4& mat4);

		Matrix4& Add(const Matrix4& mat4);
		Matrix4& Sub(const Matrix4& mat4);
		Matrix4& Mul(const Matrix4& mat4);

		Matrix4& Identity();
		Matrix4& Inverse();
		Matrix4& Transpose();

		Matrix4& SetScale(const Vector3& scale);
		Matrix4& SetTranslate(const Vector3& trans);

		Matrix4& Scale(const Vector3& scale);
		Matrix4& Translate(const Vector3& trans);
		Matrix4& RotateX(Float rotation);
		Matrix4& RotateY(Float rotation);
		Matrix4& RotateZ(Float rotation);

	public:
		Float data[16];

	};

}

#endif