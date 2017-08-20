#ifndef _Group_H__
#define _Group_H__

#include <vector>

#include "DllApi.h"
#include "Types.h"
#include "Matrix4.h"
#include "UIActor.h"

namespace Soft3D{

	class DLLAPI UIGroup :public UIActor{
	public:
		UIActor* Hit(Float x, Float y);
	private:
		Matrix4 transform;
		Matrix4 oldTransform;
		
		std::vector<UIActor*> children;

	};

}

#endif