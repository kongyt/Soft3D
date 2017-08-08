#ifndef _Pixmap_H__
#define _Pixmap_H__

#include "DllApi.h"
#include "Types.h"

namespace Soft3D{

	enum Format{
		RGBA8888 = 1,
		RGBA4444 = 2,
		RGB565   = 3,
		RGB888   = 4
	};

	class DLLAPI Pixmap{
	public:
		Pixmap(FILE* file);
		Pixmap(Byte encodedData[], UInt offset, UInt len);
		Pixmap(UInt width, UInt height, Format format);

		void DrawPixmap(const Pixmap& pixmap, UInt x, UInt y);
		void DrawPixmap(const Pixmap& pixmap, UInt x, UInt y, UInt srcX, UInt srcY, UInt srcWidth, UInt srcHeight);
		void DrawPixmap(const Pixmap& pixmap, UInt srcX, UInt srcY, UInt srcWidth, UInt srcHeight, UInt dstX, UInt dstY, UInt dstWidth, UInt dstHeight);
	private:
		Bool Decode(Byte encodeData[], UInt offset, UInt len);
		Bool AllocMemory(UInt width, UInt height, Format format);

	public:
		UInt width;
		UInt height;
		Format format;
		Byte* data;
	
	};

}



#endif