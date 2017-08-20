#ifndef _Input_Adapter_H__
#define _Input_Adapter_H__

#include "DllApi.h"
#include "InputProcessor.h"

namespace Soft3D {

	class DLLAPI InputAdapter: public InputProcessor{
	public:
		virtual Bool KeyDown(Int keyCode);
		virtual Bool KeyUp(Int keyCode);
		virtual Bool KeyTyped();
		virtual Bool TouchDown(Int screenX, Int screenY, Int keyCode);
		virtual Bool TouchDragged(Int screenX, Int screenY, Int keyCode);
		virtual Bool TouchUp(Int screenX, Int screenY, Int keyCode);
		virtual Bool MouseMoved(Int screenX, Int screenY);
		virtual Bool Scrolled(Int amount);

	};

}



#endif