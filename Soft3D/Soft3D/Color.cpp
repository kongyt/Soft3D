#include "Color.h"

namespace Soft3D {

	const Color Color::Black         = Color(0.00f, 0.00f, 0.00f, 1.00f);       // ºÚÉ«
	const Color Color::Red           = Color(1.00f, 0.00f, 0.00f, 1.00f);       // ºìÉ«
	const Color Color::Green         = Color(0.00f, 1.00f, 0.00f, 1.00f);       // ÂÌÉ«
	const Color Color::Yellow        = Color(1.00f, 1.00f, 0.00f, 1.00f);       // »ÆÉ«
	const Color Color::Blue          = Color(0.00f, 0.00f, 1.00f, 1.00f);       // À¶É«
	const Color Color::Magenta       = Color(1.00f, 0.00f, 1.00f, 1.00f);       // Ñóºì
	const Color Color::Cyan          = Color(0.00f, 1.00f, 1.00f, 1.00f);       // ÇàÉ«
	const Color Color::DarkGray      = Color(0.25f, 0.25f, 0.25f, 1.00f);       // Éî»Ò
	const Color Color::LightGray     = Color(0.75f, 0.75f, 0.75f, 1.00f);       // Ç³»Ò
	const Color Color::Brown         = Color(0.60f, 0.40f, 0.12f, 1.00f);       // ºÖÉ«
	const Color Color::PumpkinOrange = Color(0.98f, 0.625f,0.12f, 1.00f);       // ÄÏ¹Ï³È
	const Color Color::PastelPink    = Color(0.98f, 0.04f, 0.70f, 1.00f);       // ·Ûºì
	const Color Color::BarneyPurple  = Color(0.60f, 0.40f, 0.70f, 1.00f);       // °ÍÄá×Ï
	const Color Color::White         = Color(1.00f, 1.00f, 1.00f, 1.00f);       // °×É«

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
