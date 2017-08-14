#ifndef _Pixmap_H__
#define _Pixmap_H__

#include "DllApi.h"
#include "Types.h"

namespace Soft3D{


	class DLLAPI Pixmap{
	public:
		Pixmap(FILE* file);
		Pixmap(Byte encodedData[], Int offset, Int len);
		Pixmap(Int width, Int height, Int format);

		void DrawPixmap(const Pixmap& pixmap, Int x, Int y);
		void DrawPixmap(const Pixmap& pixmap, Int x, Int y, Int srcX, Int srcY, Int srcWidth, Int srcHeight);
		void DrawPixmap(const Pixmap& pixmap, Int srcX, Int srcY, Int srcWidth, Int srcHeight, Int dstX, Int dstY, Int dstWidth, Int dstHeight);
	private:
		Bool Decode(Byte encodeData[], Int offset, Int len);
		Bool AllocMemory(Int width, Int height, Int format);
		UInt GetPixelSize(Int format);

	public:
		Int width;
		Int height;
		Int format;
		Byte* data;
	
	};

}



#endif