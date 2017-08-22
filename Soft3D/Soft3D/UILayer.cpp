#include "UILayer.h"

namespace Soft3D{

	UILayer::UILayer(Float width, Float height) {
		uiCamera.SetToOrth(width, height);
		this->width = width;
		this->height = height;
	}

	UIGroup& UILayer::GetRoot() {
		return root;
	}

	Camera& UILayer::GetCamera() {
		return uiCamera;
	}

	void UILayer::Update(Float delta) {
		root.Update(delta);
	}

	void UILayer::Render(RenderContext& context) {
		context.SetCameraMatrix(uiCamera.m_combined);
		root.Render(context, 1);
	}

	Bool UILayer::KeyDown(Int keyCode) {
		return false;
	}

	Bool UILayer::KeyUp(Int keyCode) {
		return false;
	}

	Bool UILayer::KeyTyped() {
		return false;
	}

	Bool UILayer::TouchDown(Int screenX, Int screenY, Int keyCode) {
		screenY = this->height - screenY;
		UIActor* target = root.Hit(screenX, screenY);
		if (target != NULL && target->clickListener != NULL) {
			Vector2 localCoords = target->GlobalCoordsToLocal(screenX, screenY);
			Bool rs = target->clickListener->TouchDown(localCoords.x, localCoords.y, keyCode);	
			if (rs == true) {
				touchFocus.insert(std::pair<int, UIActor*>(keyCode, target));
			}
			return rs;
		}
		return false;
	}

	Bool UILayer::TouchDragged(Int screenX, Int screenY, Int keyCode) {
		screenY = this->height - screenY;
		auto itor = touchFocus.find(keyCode);
		if (itor != touchFocus.end()) {
			UIActor* target = itor->second;
			if (target != NULL && target->clickListener != NULL) {
				Vector2 localCoords = target->GlobalCoordsToLocal(screenX, screenY);
				return target->clickListener->TouchDragged(localCoords.x, localCoords.y, keyCode);
			}
		}		
		return false;
	}

	Bool UILayer::TouchUp(Int screenX, Int screenY, Int keyCode) {
		screenY = this->height - screenY;
		auto itor = touchFocus.find(keyCode);
		if (itor != touchFocus.end()) {
			UIActor* target = itor->second;
			touchFocus.erase(itor);			
			if (target != NULL && target->clickListener != NULL) {
				UIActor* hit = root.Hit(screenX, screenY);
				if (target == hit) {
					target->clickListener->Clicked();
				}

				Vector2 localCoords = target->GlobalCoordsToLocal(screenX, screenY);
				return target->clickListener->TouchUp(localCoords.x, localCoords.y, keyCode);
			}
		}
		return false;
	}

	Bool UILayer::MouseMoved(Int screenX, Int screenY) {
		screenY = this->height - screenY - 1;
		return false;
	}

	Bool UILayer::Scrolled(Int amount) {
		return false;
	}

}