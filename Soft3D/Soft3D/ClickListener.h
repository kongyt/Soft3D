#ifndef _Click_Listener_H__
#define _Click_Listener_H__

#include "DllApi.h"
#include "Types.h"

namespace Soft3D {

	class ClickListener {
	public:
		virtual Bool TouchDown(Float x, Float y, Int keyCode) {
			return true;
		}
		virtual Bool TouchDragged(Float x, Float y, Int keyCode) {
			return true;
		}
		virtual Bool TouchUp(Float x, Float y, Int keyCode) {
			return true;
		}
		virtual void Clicked() {
		
		}

	};

}

#endif