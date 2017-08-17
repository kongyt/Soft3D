#ifndef _Game_H__
#define _Game_H__

#include "DllApi.h"
#include "Types.h"
#include "Scene.h"
#include "RenderContext.h"


namespace Soft3D {

	class DLLAPI Game {
	public:		
		virtual void Start();
		void SetScene(Scene* scene);
		virtual void SetSize(int width, int height);
		virtual void Pause();
		virtual void Resume();
		virtual void Render(RenderContext& context, Float delta);
		virtual void Destroy();

	private:
		Scene* m_scene;
		int m_width;
		int m_height;
	};

}

#endif