#ifndef _Test_Scene_H__
#define _Test_Scene_H__

#include "../Soft3D/Soft3D.h"
#include "TestInput.h"
#include "TestClickListener.h"

using namespace Soft3D;


#define BUFSIZE  409600

class TestScene :public Scene, public InputAdapter {
public:

	TestScene(){
		camera.SetToPers(60, 800, 480);
		//camera.SetToOrth(1300, 480);

		root = new GameObject();

		// 从文件读取纹理图
		FILE* fp = fopen("bg2.png", "rb");
		pixmap = new Pixmap(fp);
		fclose(fp);

		video = new Video("test.mkv");
		video->Play();

		// 生成纹理
		texture = new Texture(video);
		texture->Load();

		region = new TextureRegion(texture);

		// 生成渲染对象
		sprite1 = new Sprite(region);
		sprite1->SetSize(200, 100);
		sprite1->SetRotation(45);
		sprite1->SetColor(1, 1, 1, 1);

		sprite2 = new Sprite(region);
		sprite2->SetSize(200, 100);
		sprite2->SetRotation(-45);
		sprite2->SetColor(1, 1, 1, 1);

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

		Input::SetProcessor(this);

		uiLayer = new UILayer(800, 480);
		//Input::SetProcessor(uiLayer);

		uiButton = new UIButton(region);
		uiButton->x = 0;
		uiButton->y = 0;
		uiButton->width = 400;
		uiButton->height = 240;

		uiLayer->GetRoot().AddChild(uiButton);
	}

	Bool KeyDown(Int keyCode) {
		printf("按键keyCode=%d 按下\n", keyCode);
		switch (keyCode) {
		case KeyCode::Key_Esc:
			Window::Exit();
			break;
		case KeyCode::Key_Space:
			if (isPlaying == true) {
				isPlaying = false;
				video->Play();
			}
			else {
				isPlaying = true;
				video->Pause();
			}
			
			break;
		}
		return true;
	}


	Bool KeyUp(Int keyCode) {
		printf("按键keyCode=%d 抬起\n", keyCode);
		return true;
	}

	Bool TouchDown(Int screenX, Int screenY, Int keyCode) {
		printf("鼠标按下x=%d, y = %d, keyCode=%d\n", screenX, screenY, keyCode);
		video->SetProgress(screenX / 400.0f);
		return true;
	}
	Bool TouchDragged(Int screenX, Int screenY, Int keyCode) {
		printf("鼠标拖动x=%d, y = %d, keyCode=%d \n", screenX, screenY, keyCode);
		return true;
	}
	Bool TouchUp(Int screenX, Int screenY, Int keyCode) {
		printf("鼠标抬起x=%d, y = %d, keyCode=%d \n", screenX, screenY, keyCode);
		return true;
	}

	~TestScene() {

	}

	void Show() {
		
	}

	void Resize(int width, int height) {

	}

	float dt = 0;
	void Render(RenderContext& context, Float delta) {
		dt += delta;

		video->Update(delta);

		//camera.position.x -= 1;
		//camera.Update(true);
		context.SetCameraMatrix(camera.m_combined);

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);		

		root->SetRotation(0, dt, 0);

		root->Update(delta);
		root->Render(context);

		uiLayer->Update(delta);
		uiLayer->Render(context);
	}

	void Pause() {
	
	}

	void Resume() {
	
	}

	void Destroy() {
		delete uiButton;
		delete uiLayer;
		delete sprite1;
		delete sprite2;
		delete sprite3;
		delete region;
		delete texture;
		pixmap->Destroy();
		delete pixmap;
		delete root;
	}
private:

	Camera camera;
	GameObject * root;
	Pixmap* pixmap;
	Texture* texture;
	TextureRegion* region;
	Sprite* sprite1;
	Sprite* sprite2;
	Sprite* sprite3;
	UILayer* uiLayer;
	UIActor* uiButton;

	Video* video;
	Bool isPlaying;
};

#endif