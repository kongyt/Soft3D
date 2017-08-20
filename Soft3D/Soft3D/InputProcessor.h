#ifndef _Input_Processor_H__
#define _Input_Processor_H__

#include "DllApi.h"
#include "Types.h"
#include "Input.h"

namespace Soft3D {
	class DLLAPI InputProcessor {
	public:
		virtual Bool KeyDown(Int keyCode) = 0;
		virtual Bool KeyUp(Int keyUp) = 0;
		virtual Bool KeyTyped() = 0;
		virtual Bool TouchDown(Int screenX, Int screenY, Int keyCode) = 0;
		virtual Bool TouchDragged(Int screenX, Int screenY, Int keyCode) = 0;
		virtual Bool TouchUp(Int screenX, Int screenY, Int keyCode) = 0;
		virtual Bool MouseMoved(Int screenX, Int screenY) = 0;
		virtual Bool Scrolled(Int amount) = 0;
	};

}


#endif