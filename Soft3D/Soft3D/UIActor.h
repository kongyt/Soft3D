#ifndef _UI_Actor_H__
#define _UI_Actor_H__

#include <vector>

#include "DllApi.h"
#include "Types.h"
#include "Color.h"
#include "RenderContext.h"
#include "ClickListener.h"
#include "Vector2.h"

namespace Soft3D {

	class UIGroup;

	class DLLAPI UIActor{
	public:
		virtual void Update(Float delta);
		virtual void Render(RenderContext& context, Float parentAlpha);
		void SetClickListener(ClickListener* clickListener);
		virtual UIActor* Hit(Float x, Float y);
		Vector2 ParentToLocalCoordinates(Float x, Float y);
		Vector2 GlobalCoordsToLocal(Float globalX, Float globalY);

	public:
		UIGroup* parent = NULL;
		Float x = 0;
		Float y = 0;
		Float width = 0;
		Float height = 0;
		Float originX = 0;
		Float originY = 0;
		Float scaleX = 1;
		Float scaleY = 1;
		Float rotation = 0;
		Bool  touchable = true;
		Color color = Color(1, 1, 1, 1);
		Bool  visiable;

		ClickListener* clickListener = NULL;
	};

}


#endif;