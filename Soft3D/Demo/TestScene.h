#ifndef _Test_Scene_H__
#define _Test_Scene_H__

#include <stdio.h>
#include <stdlib.h>

#include "../Soft3D/Soft3D.h"

using namespace Soft3D;

class TestScene :public Scene {
public:
	TestScene(){
		camera.SetToOrth(800, 480);
		root = new GameObject();

		// 从文件读取纹理图
		FILE* fp = fopen("bg1.png", "rb");
		Pixmap* pixmap = new Pixmap(fp);
		fclose(fp);

		// 生成纹理
		Texture* texture = new Texture(pixmap);
		texture->Init();

		// 生成渲染对象
		Sprite* sprite = new Sprite(texture);

		root->AddRenderObject(sprite); // 添加渲染对象
	}

	void Show() {
	
	}

	void Resize(int width, int height) {
	
	}

	void Render(RenderContext& context, Float delta) {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		root->Update(delta);
		root->Render(context);
	}

	void Pause() {
	
	}

	void Resume() {
	
	}
	void Destroy() {
	
	}
private:
	Camera camera;
	GameObject * root;
};

#endif