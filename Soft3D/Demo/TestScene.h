#ifndef _Test_Scene_H__
#define _Test_Scene_H__

#include <stdio.h>
#include <stdlib.h>

#include "../Soft3D/Soft3D.h"
#include "TestInput.h"

using namespace Soft3D;


class TestScene :public Scene {
public:
	TestScene(){
		camera.SetToPers(60, 1280, 720);
		//camera.SetToOrth(1300, 480);

		root = new GameObject();

		// 从文件读取纹理图
		FILE* fp = fopen("bg2.png", "rb");
		Pixmap* pixmap = new Pixmap(fp);
		fclose(fp);

		// 生成纹理
		Texture* texture = new Texture(pixmap);
		texture->Load();

		TextureRegion* region = new TextureRegion(texture);

		Sprite* sprite1;
		// 生成渲染对象
		sprite1 = new Sprite(region);
		sprite1->SetSize(200, 100);
		sprite1->SetRotation(45);
		sprite1->SetColor(1, 1, 1, 1);

		Sprite* sprite2;
		sprite2 = new Sprite(region);
		sprite2->SetSize(200, 100);
		sprite2->SetRotation(-45);
		sprite2->SetColor(1, 1, 1, 1);

		Sprite* sprite3;
		sprite3 = new Sprite(region);
		sprite3->SetSize(200, 100);
		sprite3->SetRotation(0);
		sprite3->SetColor(1, 0, 0, 1);
		
		root->AddRenderObject(sprite1); // 添加渲染对象
		root->AddRenderObject(sprite2); // 添加渲染对象
		root->AddRenderObject(sprite3); // 添加渲染对象

		root->SetPosition(0, 0, -1000);
		root->SetRotation(0, 0.5f, 0);
		root->SetScale(1,1,1);

		Input::SetProcessor(new TestInput());
	}

	void Show() {
	
	}

	void Resize(int width, int height) {

	}

	float dt = 0;
	void Render(RenderContext& context, Float delta) {
		dt += delta;
		//camera.position.x -= 1;
		//camera.Update(true);
		context.SetCameraMatrix(camera.m_combined);

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);		

		root->SetRotation(0, dt, 0);

		root->Update(delta);
		root->Render(context);

		//sprite->Render(context);
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