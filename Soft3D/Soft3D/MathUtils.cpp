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
}