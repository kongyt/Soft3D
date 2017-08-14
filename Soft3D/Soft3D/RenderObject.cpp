#include "RenderObject.h"
#include "RenderSystemInterface.h"

namespace Soft3D {

	void RenderObject::SetVisiable(Bool visiable) {
		this->visiable = visiable;
	}


	void RenderObject::Render(RenderSystemInterface* renderSystem) {
		if (this->visiable == true) {
			renderSystem->DrawRenderObject(*this);
		}
	}


}
