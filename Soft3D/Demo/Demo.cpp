#include <windows.h>
#include "Demo.h"

using namespace Soft3D;

RenderSystemInterface* renderSystem;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

void Render(){
	renderSystem->Clear(Color::Black);


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
	config.hasBorder = false;
	config.wndProc = WndProc;

	renderSystem = new RenderSystemGL();
	renderSystem->InitalizeWindow(config);

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