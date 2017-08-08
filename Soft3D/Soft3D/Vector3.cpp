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

	Vector3& Vector3::Add(const Vector3& rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;

		return *this;
	}


	Vector3& Vector3::Sub(const Vector3& rhs){
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;

		return *this;
	}

	Vector3& Vector3::Mul(Float rhs){
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;

		return *this;
	}

	Vector3& Vector3::Div(Float rhs) {
		if (MathUtils::IsZero(rhs) != true) {
			this->x /= rhs;
			this->y /= rhs;
			this->z /= rhs;
		}

		return *this;
	}

}