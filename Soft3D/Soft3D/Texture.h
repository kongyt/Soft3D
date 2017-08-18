#ifndef _Texture_H__
#define _Texture_H__

#include "DllApi.h"
#include "Pixmap.h"


namespace Soft3D {

	class DLLAPI Texture {
	public:
		Texture(Pixmap* pixmap);
		void Init();
		void Bind();
		void Destroy();

	public:
		int glTarget;
		UInt glHandle;
		Bool isLoaded;
		UInt textureId;
		Pixmap* pixmap;

	};

}

#endif