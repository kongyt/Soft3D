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
		Byte* encodedData = new Byte[n];
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

	Bool Pixmap::Decode(Byte encodeData[], Int offset, Int len) {
		UChar* pixels = stbi_load_from_memory(encodeData, len, &width, &height, &format, 0);
		if (pixels == NULL) {
			return false;
		}
		data = pixels;
		return true;
	}

	Bool Pixmap::AllocMemory(Int width, Int height, Int format) {
		data = new Byte[width*height*GetPixelSize(format)];
		return true;
	}

	UInt Pixmap::GetPixelSize(Int format) {
		return 4;
	}

}
