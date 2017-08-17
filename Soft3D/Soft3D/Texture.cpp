#include "Texture.h"
#include "Pixmap.h"

namespace Soft3D {

	Texture::Texture(Pixmap* pixmap){
		this->isLoaded = false;
		this->pixmap = pixmap;
		this->textureId = 0;
	}

}