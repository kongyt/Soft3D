#ifndef _Sprite_H__
#define _Sprite_H__

#include "DllApi.h"
#include "RenderObject.h"
#include "Color.h"
#include "TextureRegion.h"

#define VERTEX_SIZE (2+4+2)
#define SPRITE_SIZE (4 * VERTEX_SIZE)

#define POSITION_OFFSET  0
#define COLOR_OFFSET	 2
#define TEXCOORD_OFFSET  6

#define P1X			0
#define P1Y			1
#define P1R			2
#define P1G			3
#define P1B			4
#define P1A			5
#define P1U			6
#define P1V			7

#define P2X			8
#define P2Y			9
#define P2R			10
#define P2G			11
#define P2B			12
#define P2A			13
#define P2U			14
#define P2V			15

#define P3X			16
#define P3Y			17
#define P3R			18
#define P3G			19
#define P3B			20
#define P3A			21
#define P3U			22
#define P3V			23

#define P4X			24
#define P4Y			25
#define P4R			26
#define P4G			27
#define P4B			28
#define P4A			29
#define P4U			30
#define P4V			31


namespace Soft3D {

	class DLLAPI Sprite :public RenderObject{
	public:
		Sprite(TextureRegion* textureRegion);
		void SetPosition(Float x, Float y);
		void SetRotation(Float rotation);
		void SetSize(Float width, Float height);
		void SetOrigin(Float originX, Float originY);		
		void SetColor(Color color);
		void SetColor(Float r, Float g, Float b, Float a);
		void Render(RenderContext& renderContext);

	private:
		void updateVertexs();
	public:
		TextureRegion* textureRegion;
		Float vertices[SPRITE_SIZE];
		UInt  indices[4] = {0, 1, 2, 3};
		Color color;
		Float x;
		Float y;
		Float rotation;
		Float width;
		Float height;
		Float originX;
		Float originY;
		Bool isChanged;
	};

}

#endif
