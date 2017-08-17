#ifndef _Scene_H__
#define _Scene_H__

#include "DllApi.h"
#include "Types.h"
#include "RenderContext.h"

namespace Soft3D {

	class DLLAPI Scene {
	public:
		virtual void Show() = 0;
		virtual void Resize(int width, int height) = 0;
		virtual void Render(RenderContext& context, Float delta) = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void Destroy() = 0;
	};

}

#endif