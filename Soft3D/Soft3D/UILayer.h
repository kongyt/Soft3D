#ifndef _UI_Layer_H__
#define _UI_Layer_H__

#include "DllApi.h"
#include "Types.h"
#include "Camera.h"
#include "UIGroup.h"

namespace Soft3D{
	
	// UI²ã
	class DLLAPI UILayer {
	public:
		UILayer(Float width, Float height);
	private:
		UIGroup root;
		Camera uiCamera;

	};

}

#endif
