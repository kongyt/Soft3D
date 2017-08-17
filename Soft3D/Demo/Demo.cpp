#include <windows.h>
#include "../Soft3D/Soft3D.h"
#include "DemoGame.h"

using namespace Soft3D;


Window* window;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int nShow)
{
	bool result = false;
	
	WindowConfig config;
	config.hInstance = hInstance;
	config.title = TEXT("Soft3D Demo");
	config.x = 200;
	config.y = 200;
	config.width = 800;
	config.height = 480;
	config.fullScreen = false;
	config.hasBorder = true;
	config.wndProc = WndProc;

	window = new Window();
	if (!window->Initalize(new DemoGame(), config)) {
		return -1;
	}

	MSG msg = {0};
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}else{
			window->Render();
		}
	}	

	window->Destory();
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
		window->OnChangeSize(LOWORD(lParam), HIWORD(lParam));
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