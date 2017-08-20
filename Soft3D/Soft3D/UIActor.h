#ifndef _UI_Actor_H__
#define _UI_Actor_H__

#include <vector>

#include "DllApi.h"
#include "Types.h"
#include "Color.h"
#include "RenderContext.h"
#include "ClickListener.h"

namespace Soft3D {

	class Group;

	class DLLAPI UIActor{
	public:
		void Update(Float delta);
		void Render(RenderContext& context, Float parentAlpha);
		void SetClickListener(ClickListener* clickListener);
		virtual UIActor* Hit(Float x, Float y);
		Vector3 ParentToLocalCoordinates(Float x, Float y);

	public:
		Group* parent;
		Float x;
		Float y;
		Float width;
		Float height;
		Float originX;
		Float originY;
		Float scaleX = 1;
		Float scaleY = 1;
		Float rotation;
		Bool  touchable;
		Color color = Color(1, 1, 1, 1);

		ClickListener* clickListener = NULL;
	};

}


#endif;