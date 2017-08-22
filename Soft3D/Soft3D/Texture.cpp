#include "Texture.h"
#include "Pixmap.h"

#include "GLES_Support.h"

namespace Soft3D {

	Texture::Texture(Video* video) {
		this->isLoaded = true;
		this->pixmap = video->pixmap;
		this->width = video->pixmap->width;
		this->height = video->pixmap->height;
		this->textureId = 0;
	}

	Texture::Texture(Pixmap* pixmap){
		this->isLoaded = false;
		this->pixmap = pixmap;
		this->textureId = 0;
		this->width = pixmap->width;
		this->height = pixmap->height;
	}

	int ToGLPixelFormat(int pixmapFormat) {
		int rs = 0;
		switch (pixmapFormat)
		{
		case PixmapFormat::RGB:
			rs = GL_RGB;
			break;
		case PixmapFormat::RGBA:
			rs = GL_RGBA;
			break;
		default:
			break;
		}
		return rs;
	}

	void Texture::Load() {
		glTarget = GL_TEXTURE_2D;
		glGenTextures(1, &glHandle);
		glBindTexture(glTarget, glHandle);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//此为纹理过滤参数设置
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(glTarget, 0, ToGLPixelFormat(pixmap->format), pixmap->width, pixmap->height, 0, ToGLPixelFormat(pixmap->format), GL_UNSIGNED_BYTE, pixmap->data);
		glBindTexture(glTarget, 0);
		isLoaded = true;
	}
	void Texture::Reload() {
		glBindTexture(glTarget, glHandle);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//此为纹理过滤参数设置
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(glTarget, 0, ToGLPixelFormat(pixmap->format), pixmap->width, pixmap->height, 0, ToGLPixelFormat(pixmap->format), GL_UNSIGNED_BYTE, pixmap->data);
		glBindTexture(glTarget, 0);
	}

	void Texture::Unload() {
		glDeleteTextures(1, &glHandle);
	}


	void Texture::Bind() {
		Reload();
		if (isLoaded == true) {
			glBindTexture(glTarget, glHandle);
		}
		
	}

	void Texture::Unbind() {
		glBindTexture(glTarget, 0);
	}

	void Texture::Destroy(){
		if (isLoaded == true) {
			Unload();
		}	
	}

}