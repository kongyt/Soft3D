#ifndef _Render_Object_H__
#define _Render_Object_H__

#include "DllApi.h"
#include "RenderData.h"

namespace Soft3D {

	class GameObject;
	class RenderSystemInterface;

	enum DLLAPI RenderType {
		Points,
		Lines,
		LineStrip,
		LineLoop,
		Triangles,
		TriangleStrip,
		TriangleFan,
	};

	class DLLAPI RenderObject {
	public:
		void SetVisiable(Bool visiable);
		void Render(RenderSystemInterface* renderSystem);

	public:
		GameObject* owner;
		Bool visiable;
		RenderType renderType;
		RenderData* renderData;
	};
}

#endif