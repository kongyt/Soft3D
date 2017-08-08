#include "Viewport.h"

namespace Soft3D {

	Viewport::Viewport(Int width, Int height) {
		this->x = 0;
		this->y = 0;
		this->width = width;
		this->height = height;
	}

	Viewport::Viewport(Int x, Int y, Int width, Int height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

}