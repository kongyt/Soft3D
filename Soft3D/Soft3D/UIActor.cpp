#include "UIActor.h"
#include "MathUtils.h"
#include "UIGroup.h"

namespace Soft3D {


	void UIActor::Update(Float delta) {
	
	}

	void UIActor::Render(RenderContext& context, Float parentAlpha) {
	

	}
	void UIActor::SetClickListener(ClickListener* clickListener) {
		this->clickListener = clickListener;
	}

	UIActor* UIActor::Hit(Float x, Float y) {
		if (touchable == true && x >= 0 && x < width && y >= 0 && y < height) {
			return this;
		}
		else {
			return NULL;
		}
	}

	Vector2 UIActor::ParentToLocalCoordinates(Float parentCoordsX, Float parentCoordsY) {
		float rotation = this->rotation;
		float scaleX = this->scaleX;
		float scaleY = this->scaleY;
		float childX = x;
		float childY = y;
		if (MathUtils::IsZero(rotation)) {
			if (scaleX == 1 && scaleY == 1) {
				parentCoordsX -= childX;
				parentCoordsY -= childY;
			}
			else {
				float originX = this->originX;
				float originY = this->originY;
				parentCoordsX = (parentCoordsX - childX - originX) / scaleX + originX;
				parentCoordsY = (parentCoordsY - childY - originY) / scaleY + originY;
			}
		}
		else {
			float cosTheta = (float)cos(rotation / 180.0f * MathUtils::Pi());
			float sinTheta = (float)sin(rotation / 180.0f * MathUtils::Pi());
			float originX = this->originX;
			float originY = this->originY;
			float tox = parentCoordsX - childX - originX;
			float toy = parentCoordsY - childY - originY;
			parentCoordsX= (tox * cosTheta + toy * sinTheta) / scaleX + originX;
			parentCoordsY = (tox * -sinTheta + toy * cosTheta) / scaleY + originY;
		}
		return Vector2(parentCoordsX,parentCoordsY);
	}

	Vector2 UIActor::GlobalCoordsToLocal(Float globalX, Float globalY) {
		if (parent == NULL) return Vector2(globalX, globalY);
		Vector2 parentCoords = parent->GlobalCoordsToLocal(globalX, globalY);
		return ParentToLocalCoordinates(parentCoords.x, parentCoords.y);
	}

}