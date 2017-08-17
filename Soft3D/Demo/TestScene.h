#ifndef _Test_Scene_H__
#define _Test_Scene_H__

#include "../Soft3D/Soft3D.h"

using namespace Soft3D;

class TestScene :public Scene {
public:
	TestScene(){
		camera.SetToOrth(800, 480);
	}

	void Show() {
	
	}

	void Resize(int width, int height) {
	
	}

	void Render(RenderContext& context, Float delta) {
		glClearColor(0.75f, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Pause() {
	
	}

	void Resume() {
	
	}
	void Destroy() {
	
	}
private:
	Camera camera;
};

#endif