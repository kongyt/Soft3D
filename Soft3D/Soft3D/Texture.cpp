#include "Texture.h"
#include "Pixmap.h"

#include "GLES_Support.h"

namespace Soft3D {

	Texture::Texture(Pixmap* pixmap){
		this->isLoaded = false;
		this->pixmap = pixmap;
		this->textureId = 0;
	}

	void Texture::Init() {
		glTarget = GL_TEXTURE_2D;
		glGenTextures(1, &glHandle);
		Bind();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//此为纹理过滤参数设置
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(glTarget, 0, GL_RGBA, pixmap->width, pixmap->height, 0, GL_RGBA8_OES, GL_UNSIGNED_BYTE, pixmap->data);
		glBindTexture(glTarget, 0);
	}


	void Texture::Bind() {
		glBindTexture(glTarget, glHandle);
	}

	void Texture::Destroy(){

	}

}