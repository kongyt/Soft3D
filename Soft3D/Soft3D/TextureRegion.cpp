#include "TextureRegion.h"

namespace Soft3D {

	TextureRegion::TextureRegion(Texture* texture) {
		this->texture = texture;
		SetRegion(0, 0, texture->width, texture->height);
	}

	TextureRegion::TextureRegion(Texture* texture, int x, int y, int width, int height) {
		this->texture = texture;
		SetRegion(x, y, width, height);
	}

	void TextureRegion::SetRegion(int x, int y, int width, int height){
		u1 = (float)x / texture->width;
		v1 = (float)y / texture->height;
		u2 = (float)(x+width) / texture->width;
		v2 = (float)(y+height) / texture->height;
	}

}