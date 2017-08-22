#include "UIGroup.h"

namespace Soft3D {

	void UIGroup::Render(RenderContext& context, Float parentAlpha) {
	/*	transform.Identity().Translate(Vector3(x+originX, y+originY, 0)).RotateZ(rotation).Scale(Vector3(scaleX, scaleY, 1));
		context.PushTransformMatrix(transform);*/

		for (auto itor = children.begin(); itor != children.end(); ++itor) {
			(*itor)->Render(context, parentAlpha*this->color.a);
		}
		
		/*context.PopTransformMatrix();*/
	}

	UIActor* UIGroup::Hit(Float x, Float y) {
		for (auto itor = children.begin(); itor != children.end(); ++itor) {
			Vector2 pos = (*itor)->ParentToLocalCoordinates(x, y);
			UIActor* hit = (*itor)->Hit(pos.x, pos.y);
			if (hit != NULL) {
				return hit;
			}
		}
		return UIActor::Hit(x, y);
	}

	void UIGroup::AddChild(UIActor* child) {
		children.push_back(child);
	}

}
