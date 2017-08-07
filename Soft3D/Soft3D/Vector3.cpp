#include "Vector3.h"
#include "MathUtils.h"

namespace Soft3D {

	Vector3::Vector3() {
		this->a = 0.0f;
		this->b = 0.0f;
		this->c = 0.0f;
	}

	Vector3::Vector3(Float a, Float b, Float c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}

	Vector3* Vector3::Clone() {
		return new Vector3(a, b, c);
	}

	Vector3& Vector3::Add(const Vector3& rhs) {
		this->a += rhs.a;
		this->b += rhs.b;
		this->c += rhs.c;

		return *this;
	}


	Vector3& Vector3::Sub(const Vector3& rhs){
		this->a -= rhs.a;
		this->b -= rhs.b;
		this->c -= rhs.c;

		return *this;
	}

	Vector3& Vector3::Mul(Float rhs){
		this->a * rhs;
		this->b * rhs;
		this->c * rhs;

		return *this;
	}

	Vector3& Vector3::Div(Float rhs) {
		if (MathUtils::IsZero(rhs) != true) {
			this->a / rhs;
			this->b / rhs;
			this->c / rhs;
		}

		return *this;
	}

}