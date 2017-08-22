#ifndef _UI_Layer_H__
#define _UI_Layer_H__

#include <map>

#include "DllApi.h"
#include "Types.h"
#include "Camera.h"
#include "UIGroup.h"
#include "InputAdapter.h"
#include "Vector2.h"
#include "RenderContext.h"

namespace Soft3D{
	
	// UI²ã
	class DLLAPI UILayer :public InputAdapter{
	public:
		UILayer(Float width, Float height);
		UIGroup& GetRoot();
		Camera& GetCamera();
		void Update(Float delta);
		void Render(RenderContext& context);
		virtual Bool KeyDown(Int keyCode);
		virtual Bool KeyUp(Int keyCode);
		virtual Bool KeyTyped();
		virtual Bool TouchDown(Int screenX, Int screenY, Int keyCode);
		virtual Bool TouchDragged(Int screenX, Int screenY, Int keyCode);
		virtual Bool TouchUp(Int screenX, Int screenY, Int keyCode);
		virtual Bool MouseMoved(Int screenX, Int screenY);
		virtual Bool Scrolled(Int amount);
	private:
		UIGroup root;
		Camera uiCamera;
		Float width;
		Float height;

		std::map<Int, UIActor*> touchFocus;
	};

}

#endif
