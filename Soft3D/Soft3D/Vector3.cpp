#include "Vector3.h"
#include "MathUtils.h"

namespace Soft3D {

	Vector3::Vector3() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	Vector3::Vector3(Float x, Float y, Float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3* Vector3::Clone() {
		return new Vector3(x, y, z);
	}

	Vector3& Vector3::Set(const Vector3& vec) {
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
		return *this;
	}

	Vector3& Vector3::Set(Float x, Float y, Float z) {
		this->x = x;
		this->y = y;
		this->z = z;
		return *this;
	}

	Vector3& Vector3::Add(const Vector3& vec) {
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;

		return *this;
	}

	Vector3& Vector3::Add(Float v1, Float v2, Float v3) {
		this->x += v1;
		this->y += v2;
		this->z += v3;

		return *this;
	}

	Vector3& Vector3::Sub(const Vector3& vec) {
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;

		return *this;
	}

	Vector3& Vector3::Sub(Float v1, Float v2, Float v3) {
		this->x -= v1;
		this->y -= v2;
		this->z -= v3;

		return *this;
	}

	Vector3& Vector3::Scl(Float scalar) {
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;

		return *this;
	}

	Vector3& Vector3::Scl(Float scalarX, Float scalarY, Float scalarZ) {
		this->x *= scalarX;
		this->y *= scalarY;
		this->z *= scalarZ;

		return *this;
	}

	Vector3& Vector3::Nor() {
		Float len2 = Len2();
		if (MathUtils::IsZero(len2) || MathUtils::IsEqual(len2, 1.0f)) {
			return *this;
		}
		return Scl(1.0f / sqrtf(len2));
	}

	Float Vector3::Dot(const Vector3& vec) {
		return x * vec.x + y * vec.y + z * vec.z;
	}

	Vector3& Vector3::Crs(const Vector3& vec) {
		return Set(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
	}


	// ×ó³Ë¾ØÕó
	Vector3& Vector3::Mul(const Matrix4& mat) {
		Float tmpX = x * mat.data[M00] + y * mat.data[01] + z * mat.data[02] + mat.data[03];
		Float tmpY = x * mat.data[M10] + y * mat.data[11] + z * mat.data[12] + mat.data[13];
		Float tmpZ = x * mat.data[M20] + y * mat.data[21] + z * mat.data[22] + mat.data[23];
		return Set(tmpX, tmpY, tmpZ);
	}

	Vector3& Vector3::Prj(const Matrix4& mat) {
		Float w = 1.0f / (x * mat.data[M30] + y * mat.data[M31] + z * mat.data[M32] + mat.data[M33]);
		Float tmpX = (x * mat.data[M00] + y * mat.data[01] + z * mat.data[02] + mat.data[03]) * w;
		Float tmpY = (x * mat.data[M10] + y * mat.data[11] + z * mat.data[12] + mat.data[13]) * w;
		Float tmpZ = (x * mat.data[M20] + y * mat.data[21] + z * mat.data[22] + mat.data[23]) * w;
		return Set(tmpX, tmpY, tmpZ);
	}

	// result = a + (b - a) * t
	//        = a + b * t - a * t
	//        = a * (1 - t) + b * t
	Vector3& Vector3::Lerp(const Vector3& target, float t) {
		return Scl(1.0f - t).Add(target.x * t, target.y * t, target.z * t);
	}

	Vector3& Vector3::Limit(Float limit) {
		if (Len2() > limit * limit) {
			Nor().Scl(limit);
		}
		return *this;
	}
	Vector3& Vector3::Clamp(Float min, Float max) {
		Float l2 = Len2();
		if (MathUtils::IsZero(l2)) {
			return *this;
		}
		if (l2 > max * max) {
			return Nor().Scl(max);
		}
		if (l2 < min * min) {
			return Nor().Scl(min);
		}
		return *this;
	}

	Float Vector3::Len2() {
		return x * x + y * y + z * z;
	}

	Float Vector3::Len() {
		return sqrtf(Len2());
	}

	Bool  Vector3::Equal(const Vector3& vec) {
		return (MathUtils::IsEqual(x, vec.x) &&
			MathUtils::IsEqual(y, vec.y) &&
			MathUtils::IsEqual(z, vec.z));
	}

	Float Vector3::Dst2(const Vector3& vec) {
		return Vector3().Add(*this).Sub(vec).Len2();
	}

	Float Vector3::Dst(const Vector3& vec) {
		return sqrtf(Vector3().Add(*this).Sub(vec).Len2());
	}

}