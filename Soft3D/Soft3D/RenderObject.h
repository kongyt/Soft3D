#ifndef _Render_Object_H__
#define _Render_Object_H__

#include "DllApi.h"
#include "Types.h"
#include "RenderContext.h"

namespace Soft3D {

	class GameObject;

	class DLLAPI RenderObject {
	public:
		void SetVisiable(Bool visiable) { this->visiable = visiable; };
		virtual void Render(RenderContext& renderContext) = 0;

	public:
		GameObject* owner;
		Bool visiable;
	};
}

#endif