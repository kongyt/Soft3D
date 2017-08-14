#include <windows.h>
#include "Demo.h"
#include "../Soft3D/Debug.h"
#include "../Soft3D/RenderData.h"
#include "../Soft3D/RenderObject.h"
#include "../Soft3D/GameObject.h"

using namespace Soft3D;

RenderSystemInterface* renderSystem;
Camera* camera;
RenderData* fivePoints;
RenderObject renderObj;
GameObject gameObj;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

void Render(){

	renderSystem->Clear(Color::Black);

	gameObj.Render(renderSystem);

	renderSystem->SwapBuffer();
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int nShow)
{
	bool result = false;
	
	RenderConfig config;
	config.hInstance = hInstance;
	config.title = TEXT("Soft3D Demo");
	config.x = 200;
	config.y = 200;
	config.width = 800;
	config.height = 480;
	config.fullScreen = false;
	config.hasBorder = true;
	config.wndProc = WndProc;

	renderSystem = new RenderSystemGL();
	renderSystem->InitalizeWindow(config);

	camera = new Camera();
	//camera->SetToPers(60.0f, 800, 480);
	camera->SetToOrth(800, 480);
	//Vector3 tmp;
	//tmp.Set(1, 2, -3);
	//camera->m_projection.Prj(tmp);
	//bool rs = camera->m_frustum.PointInFrustum(tmp);
	camera->Apply(renderSystem);
	//Debug::Info(Debug::ToString(camera->m_combined));

	fivePoints = RenderData::CreateRenderData(6, 7, 0);
	for (int i = 0; i < 6; i++) {
		fivePoints->verticesData[i * 7 + 0] = 100+i*200;
		fivePoints->verticesData[i * 7 + 1] = 100+ (rand() % 100);
		fivePoints->verticesData[i * 7 + 2] = -100;
		fivePoints->verticesData[i * 7 + 3] = (rand() % 100) / 100.0;
		fivePoints->verticesData[i * 7 + 4] = (rand()%100)/100.0;
		fivePoints->verticesData[i * 7 + 5] = (rand() % 100) / 100.0;
		fivePoints->verticesData[i * 7 + 6] = 1.0;
	}

	renderObj.renderData = fivePoints;
	renderObj.renderType = RenderType::Points;
	renderObj.renderType = RenderType::Lines;
	renderObj.renderType = RenderType::LineStrip;
	renderObj.renderType = RenderType::Triangles;
	renderObj.renderType = RenderType::TriangleStrip;
	renderObj.renderType = RenderType::TriangleFan;
	renderObj.visiable = true;

	renderSystem->SetBrushColor(Color(1, 1, 1, 1));

	gameObj.AddRenderObject(&renderObj);
	gameObj.position = Vector3(100,0,0);
	gameObj.transformMatrix.SetToTranslation(gameObj.position);

	MSG msg = {0};
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}else{
			Render();
		}
	}	

	renderSystem->DestoryWindow();
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;

	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	case WM_SIZE:
		renderSystem->OnChangeSize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		default:
			break;
		}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}