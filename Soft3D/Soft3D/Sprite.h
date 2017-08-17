#ifndef _Sprite_H__
#define _Sprite_H__

#include "DllApi.h"
#include "RenderObject.h"
#include "Color.h"
#include "Texture.h"

#define VERTEX_SIZE (3+1+2)
#define SPRITE_SIZE (4 * VERTEX_SIZE)

namespace Soft3D {

	class DLLAPI Sprite :public RenderObject{
	public:
		Sprite(Texture* texture);
		void Render(RenderContext& renderContext);
	public:
		Texture* texture;
		Float vertices[SPRITE_SIZE];
		Color color;
		Float width;
		Float height;
		Float originX;
		Float originY;
	};

}

#endif
