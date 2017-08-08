#include "Vector4.h"
#include "MathUtils.h"

namespace Soft3D {

	Vector4::Vector4() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	}

	Vector4::Vector4(Float x, Float y, Float z, Float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4* Vector4::Clone() {
		return new Vector4(x, y, z, w);
	}

	Vector4& Vector4::Add(const Vector4& rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		this->w += rhs.w;

		return *this;
	}


	Vector4& Vector4::Sub(const Vector4& rhs){
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		this->w -= rhs.w;

		return *this;
	}

	Vector4& Vector4::Mul(Float rhs){
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
		this->w *= rhs;

		return *this;
	}

	Vector4& Vector4::Div(Float rhs) {
		if (MathUtils::IsZero(rhs) != true) {
			this->x /= rhs;
			this->y /= rhs;
			this->z /= rhs;
			this->w /= rhs;
		}

		return *this;
	}

}