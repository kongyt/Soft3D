#include "MathUtils.h"

namespace Soft3D {

	Float MathUtils::Epsilon() {
		return 0.000001f;
	}

	Float MathUtils::Pi() {
		return 3.1415927f;
	}

	Bool MathUtils::IsZero(Float val) {
		if (Abs(val) < Epsilon()) {
			return true;
		}
		else {
			return false;
		}
	}

	Bool MathUtils::IsEqual(Float val1, Float val2){
		return IsZero(val1 - val2);
	}

	Float MathUtils::Rad2Deg(Float radian) {
		return radian * 180.0f / Pi();
	}

	Float MathUtils::Min(Float v1, Float v2) {
		return v1 < v2 ? v1 : v2;
	}

	Float MathUtils::Max(Float v1, Float v2) {
		return v1 > v2 ? v1 : v2;
	}

	Float MathUtils::Clamp(Float value, Float v1, Float v2) {
		Float minVal = Min(v1, v2);
		Float maxVal = Max(v1, v2);
		if (value < minVal) {
			return minVal;
		}
		else if (value > maxVal) {
			return maxVal;
		}
		else {
			return value;
		}
	}

	Float MathUtils::Abs(Float val) {
		if (val < 0) {
			return -val;
		}
		else {
			return val;
		}
	}

	Float MathUtils::Distance(const Vector3& point, const Vector4& plane) {
		return point.x * plane.x + point.y * plane.y + point.z * plane.z + plane.w;
	}

	void MathUtils::TransformVector4(Vector4& out, const Vector4& vec4, const Matrix4& mat) {
		out.x = mat.data[M00] * vec4.x + mat.data[M10] * vec4.y + mat.data[M20] * vec4.z + mat.data[M30] * vec4.z;
		out.y = mat.data[M01] * vec4.x + mat.data[M11] * vec4.y + mat.data[M21] * vec4.z + mat.data[M31] * vec4.z;
		out.z = mat.data[M02] * vec4.x + mat.data[M12] * vec4.y + mat.data[M22] * vec4.z + mat.data[M32] * vec4.z;
		out.w = mat.data[M03] * vec4.x + mat.data[M13] * vec4.y + mat.data[M23] * vec4.z + mat.data[M33] * vec4.z;
	}

	void MathUtils::CrossProduct3(Vector3& out, const Vector3& u, const Vector3& v) {
		out.x = u.y * v.z - v.y * u.z;
		out.y = -u.x * v.z + v.x * u.z;
		out.z = u.x * v.y - v.x * u.y;
	}

	void MathUtils::GetPointEquation(Vector4& out, const Vector3& p1, const Vector3& p2, const Vector3& p3) {
		Vector3 v1, v2;
		v1.x = p3.x - p1.x;
		v1.y = p3.y - p1.y;
		v1.z = p3.z - p1.z;

		v2.x = p2.x - p1.x;
		v2.y = p2.y - p1.y;
		v2.z = p2.z - p1.z;

		Vector3 tmp;
		CrossProduct3(tmp, v1, v2);
	

		// TODO


	}
}