#ifndef _Texture_Region_H__
#define _Texture_Region_H__

#include "DllApi.h"
#include "Texture.h"
#include "Types.h"


namespace Soft3D {

	class DLLAPI TextureRegion {
	public:
		TextureRegion(Texture* texture);
		TextureRegion(Texture* texture, int x, int y, int width, int height);

		void SetRegion(int x, int y, int width, int height);

	public:
		Texture* texture;
		Float u1;
		Float v1;
		Float u2;
		Float v2;
		Int   regionWidth;
		Int   regionHeight;


	};

}

#endif