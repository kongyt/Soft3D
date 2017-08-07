#include "Color.h"

namespace Soft3D {

	Color::Color() {
		this->r = 0.0f;
		this->g = 0.0f;
		this->b = 0.0f;
		this->a = 0.0f;
	}

	Color::Color(Float r, Float g, Float b, Float a) {
		this->r = MathUtils::Clamp(r, 0.0f, 1.0f);
		this->g = MathUtils::Clamp(g, 0.0f, 1.0f);
		this->b = MathUtils::Clamp(b, 0.0f, 1.0f);
		this->a = MathUtils::Clamp(a, 0.0f, 1.0f);
	}

	Color::Color(UInt color) {
		this->r = ((color & 0xFF000000) >> 24) / 255.0f;
		this->g = ((color & 0x00FF0000) >> 16) / 255.0f;
		this->b = ((color & 0x0000FF00) >> 8) / 255.0f;
		this->a = (color & 0x000000FF) / 255.0f;
	}
	
	Color* Color::Clone() {
		return new Color(r, g, b, a);
	}

	UInt Color::ToUint() {
		UInt color = 0;
		color = (color | ((UInt)(r * 255) & 0x000000FF)) << 8;
		color = (color | ((UInt)(g * 255) & 0x000000FF)) << 8;
		color = (color | ((UInt)(b * 255) & 0x000000FF)) << 8;
		color = color | ((UInt)(a * 255) & 0x000000FF);
		return color;
	}

}
