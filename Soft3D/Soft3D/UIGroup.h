#ifndef _UI_Group_H__
#define _UI_Group_H__

#include <vector>

#include "DllApi.h"
#include "Types.h"
#include "Matrix4.h"
#include "UIActor.h"

namespace Soft3D{

	class DLLAPI UIGroup :public UIActor{
	public:
		virtual void Render(RenderContext& context, Float parentAlpha);
		void AddChild(UIActor* child);
		UIActor* Hit(Float x, Float y);
	private:
		Matrix4 transform;
		Matrix4 oldTransform;
		
		std::vector<UIActor*> children;

	};

}

#endif