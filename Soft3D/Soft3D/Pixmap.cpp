#include <stdio.h>
#include <stdlib.h>

#include "Pixmap.h"
#define STBI_HEADER_FILE_ONLY
#define STBI_NO_FAILURE_STRINGS
#include "stb_image.c"


namespace Soft3D {
	

	Pixmap::Pixmap(FILE* file) {
		long n = 0;
		fseek(file, 0, 2);
		n = ftell(file);
		fseek(file, 0, 0);
		Byte* encodedData = new Byte[n];
		fread(encodedData, sizeof(Byte), n, file);
		Decode(encodedData, 0, n);
		delete encodedData;
	}

	Pixmap::Pixmap(Byte encodedData[], Int offset, Int len) {
		Decode(encodedData, offset, len);
	}

	Pixmap::Pixmap(Int width, Int height, Int format) {
		AllocMemory(width, height, format);
		this->width = width;
		this->height = height;
		this->format = format;
	}

	void Pixmap::DrawPixmap(const Pixmap& pixmap, Int x, Int y) {
	
	}

	void Pixmap::DrawPixmap(const Pixmap& pixmap, Int x, Int y, Int srcX, Int srcY, Int srcWidth, Int srcHeight) {
	
	}


	void Pixmap::DrawPixmap(const Pixmap& pixmap, Int srcX, Int srcY, Int srcWidth, Int srcHeight, Int dstX, Int dstY, Int dstWidth, Int dstHeight) {
	
	}

	PixmapFormat StbiToPixmapFormat(int format) {
		PixmapFormat rs = None;
		switch (format)
		{
		case STBI_rgb:
			rs = PixmapFormat::RGB;
			break;
		case STBI_rgb_alpha:
			rs = PixmapFormat::RGBA;
			break;
		default:
			break;
		}
		return rs;
	}

	Bool Pixmap::Decode(Byte encodeData[], Int offset, Int len) {
		UChar* pixels = stbi_load_from_memory(encodeData, len, &width, &height, &format, 0);
		if (pixels == NULL) {
			return false;
		}
		
		data = pixels;
		
		format = StbiToPixmapFormat(format);
		if (format != PixmapFormat::None) {
			return true;
		}else{
			return false;
		}
	}

	Bool Pixmap::AllocMemory(Int width, Int height, Int format) {
		data = (Byte*)malloc(width*height*GetPixelSize(format));
		for (int i = 0; i < width*height*GetPixelSize(format); i++) {
			data[i] = 255;
		}
		return true;
	}

	UInt Pixmap::GetPixelSize(Int format) {
		switch (format)
		{
		case PixmapFormat::RGB:
			return 3;
		case PixmapFormat::RGBA:
			return 4;
		default:
			return 0;
		}
	}

	
	void Pixmap::Destroy() {
		free(data);
		data = NULL;
	}
}
