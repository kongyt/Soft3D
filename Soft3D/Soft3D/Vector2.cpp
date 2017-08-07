#include "Vector2.h"
#include "MathUtils.h"

namespace Soft3D {

	Vector2::Vector2() {
		this->a = 0.0f;
		this->b = 0.0f;
	}

	Vector2::Vector2(Float a, Float b) {
		this->a = a;
		this->b = b;
	}

	Vector2* Vector2::Clone() {
		return new Vector2(a, b);
	}
	
	Vector2& Vector2::Add(const Vector2& rhs) {
		this->a += rhs.a;
		this->b += rhs.b;

		return *this;
	}

	Vector2& Vector2::Sub(const Vector2& rhs) {
		this->a -= rhs.a;
		this->b -= rhs.b;

		return *this;
	}

	Vector2& Vector2::Mul(Float rhs) {
		this->a * rhs;
		this->b * rhs;

		return *this;
	}

	Vector2& Vector2::Div(Float rhs) {
		if (MathUtils::IsZero(rhs) != true) {
			this->a / rhs;
			this->b / rhs;
		}		

		return *this;
	}

}