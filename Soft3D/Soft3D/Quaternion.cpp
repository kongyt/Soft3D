#include "Quaternion.h"

namespace Soft3D {

	Quaternion::Quaternion() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	}

	Quaternion::Quaternion(Float x, Float y, Float z, Float w) {
		this->Set(x, y, z, w);
	}

	Quaternion::Quaternion(Float yaw, Float pitch, Float roll) {
		this->SetEulerAngle(yaw, pitch, roll);
	}

	Quaternion* Quaternion::Clone() {
		return new Quaternion(x, y, z, w);
	}

	Float Quaternion::Dot(const Quaternion& rhs) {
		return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
	}

	Quaternion Quaternion::Lerp(const Quaternion& rhs, Float t) {
		return Quaternion(
			(1 - t) * x + t * rhs.x,
			(1 - t) * y + t * rhs.y,
			(1 - t) * z + t * rhs.z,
			(1 - t) * w + t * rhs.w);
	}

	Quaternion Quaternion::Slerp(const Quaternion& rhs, Float t) {
		Float cosTheta = Dot(rhs); // 模长为1.0f，故cos值为点积

		Float sign;
		if (cosTheta < 0.0f) {
			cosTheta = -cosTheta;
			sign = -1.0f;
		}
		else {
			sign = 1.0f;
		}

		Float c1, c2;
		if (cosTheta > 1.0f - MathUtils::Epsilon()) {
			c2 = t;
			c1 = 1.0f - t;
		}
		else {
			Float theta = acos(cosTheta);
			Float sinTheta = sin(theta);
			Float tTheta = t * theta;
			Float invSinTheta = 1.0f / sinTheta;
			c2 = sin(tTheta) * invSinTheta;
			c1 = sin(theta - tTheta) * invSinTheta;
		}

		c2 *= sign;

		return Quaternion(x * c1 + rhs.x * c2, y * c1 + rhs.y, z * c1 + rhs.z, w * c1 + rhs.w * c2);
	}

	Float Quaternion::Angle(const Quaternion& rhs) {
		Float cosTheta = Dot(rhs);  // 模长为1.0f，故cos值为点积

		if (cosTheta < 0.0f) {
			cosTheta = -cosTheta;
		}

		Float theta = acos(cosTheta);
		return 2 * MathUtils::Rad2Deg(theta);
	}

	void Quaternion::SetEulerAngle(Float yaw, Float pitch, Float roll) {
		Float  angle;
		Float  sinRoll, sinPitch, sinYaw, cosRoll, cosPitch, cosYaw;

		angle = yaw * 0.5f;
		sinYaw = sin(angle);
		cosYaw = cos(angle);

		angle = pitch * 0.5f;
		sinPitch = sin(angle);
		cosPitch = cos(angle);

		angle = roll * 0.5f;
		sinRoll = sin(angle);
		cosRoll = cos(angle);

		Float _y = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch*sinYaw;
		Float _x = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch*cosYaw;
		Float _z = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch*sinYaw;
		Float _w = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch*sinYaw;

		float mag = _x *_x + _y*_y + _z *_z + _w*_w;
		x = _x / mag;
		y = _y / mag;
		z = _z / mag;
		w = _w / mag;
	}

	void Quaternion::Set(Float x, Float y, Float z, Float w) {
		Float mag = x * x + y * y + z * z + w * w;
		this->x = x / mag;
		this->y = y / mag;
		this->z = z / mag;
		this->w = w / mag;
	}

	Quaternion Quaternion::Conjugate() {
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion Quaternion::Inverse() {
		return Quaternion(-x, -y, -z, w);
	}

	Vector3 Quaternion::EulerAngle() {
		Float yaw = atan2(2 * (w * x + z * y), 1 - 2 * (x * x + y * y));
		Float pitch = asin(MathUtils::Clamp(2 * (w * y - x * z), -1.0f, 1.0f));
		Float roll = atan2(2 * (w * z + x * y), 1 - 2 * (z * z + y * y));
		return Vector3(MathUtils::Rad2Deg(yaw), MathUtils::Rad2Deg(pitch), MathUtils::Rad2Deg(roll));
	}


	void Quaternion::ToMatrix4(Matrix4& mat4) {
		float xx = x * x;
		float xy = x * y;
		float xz = x * z;
		float xw = x * w;
		float yy = y * y;
		float yz = y * z;
		float yw = y * w;
		float zz = z * z;
		float zw = z * w;

		// Set matrix from quaternion
		mat4.data[M00] = 1 - 2 * (yy + zz);
		mat4.data[M01] = 2 * (xy - zw);
		mat4.data[M02] = 2 * (xz + yw);
		mat4.data[M03] = 0;
		mat4.data[M10] = 2 * (xy + zw);
		mat4.data[M11] = 1 - 2 * (xx + zz);
		mat4.data[M12] = 2 * (yz - xw);
		mat4.data[M13] = 0;
		mat4.data[M20] = 2 * (xz - yw);
		mat4.data[M21] = 2 * (yz + xw);
		mat4.data[M22] = 1 - 2 * (xx + yy);
		mat4.data[M23] = 0;
		mat4.data[M30] = 0;
		mat4.data[M31] = 0;
		mat4.data[M32] = 0;
		mat4.data[M33] = 1;
	}
}