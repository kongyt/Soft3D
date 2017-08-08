#include "Vector2.h"
#include "MathUtils.h"

namespace Soft3D {

	Vector2::Vector2() {
		this->x = 0.0f;
		this->y = 0.0f;
	}

	Vector2::Vector2(Float x, Float y) {
		this->x = x;
		this->y = y;
	}

	Vector2* Vector2::Clone() {
		return new Vector2(x, y);
	}
	
	Vector2& Vector2::Add(const Vector2& rhs) {
		this->x += rhs.x;
		this->y += rhs.y;

		return *this;
	}

	Vector2& Vector2::Sub(const Vector2& rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;

		return *this;
	}

	Vector2& Vector2::Mul(Float rhs) {
		this->x *= rhs;
		this->y *= rhs;

		return *this;
	}

	Vector2& Vector2::Div(Float rhs) {
		if (MathUtils::IsZero(rhs) != true) {
			this->x /= rhs;
			this->y /= rhs;
		}		

		return *this;
	}

}