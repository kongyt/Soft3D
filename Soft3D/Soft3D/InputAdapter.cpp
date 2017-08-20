#include "InputAdapter.h"

namespace Soft3D {

	Bool InputAdapter::KeyDown(Int keyCode) {
		return false;
	}

	Bool InputAdapter::KeyUp(Int keyCode) {
		return false;
	}

	Bool InputAdapter::KeyTyped() {
		return false;
	}

	Bool InputAdapter::TouchDown(Int screenX, Int screenY, Int keyCode){
		return false;
	}

	Bool InputAdapter::TouchDragged(Int screenX, Int screenY, Int keyCode) {
		return false;
	}

	Bool InputAdapter::TouchUp(Int screenX, Int screenY, Int keyCode){
		return false;
	}

	Bool InputAdapter::MouseMoved(Int screenX, Int screenY) {	
		return false;
	}

	Bool InputAdapter::Scrolled(Int amount) {
		return false;
	}


}