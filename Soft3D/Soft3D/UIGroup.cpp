#include "UIGroup.h"

namespace Soft3D {

	UIActor* UIGroup::Hit(Float x, Float y) {
		for (auto itor = children.begin(); itor != children.end(); ++itor) {
			Vector3 pos = (*itor)->ParentToLocalCoordinates(x, y);
			UIActor* hit = (*itor)->Hit(pos.x, pos.y);
			if (hit != NULL) {
				return hit;
			}
		}
		return UIActor::Hit(x, y);
	}

}
