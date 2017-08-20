#include <windows.h>
#include <fcntl.h>
#include <io.h>

#include "../Soft3D/Soft3D.h"
#include "DemoGame.h"

using namespace Soft3D;


Window* window;
Bool mouseLeftBtnDown = false;
Bool mouseMidBtnDown = false;
Bool mouseRightBtnDown = false;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

void RedirectIOToConsole()
{
	BOOL bResult;

	// Could try attaching to the current console but there might not
	// be one and the output format is somewhat ugly.
	//AttachConsole(ATTACH_PARENT_PROCESS);

	// allocate a console for this app
	bResult = AllocConsole();

	if (bResult)
	{
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);
	}
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int nShow)
{
	bool result = false;
	
	RedirectIOToConsole();
	WindowConfig config;
	config.hInstance = hInstance;
	config.title = TEXT("Soft3D Demo");
	config.x = 200;
	config.y = 200;
	config.width = 1280;
	config.height = 720;
	config.hasBorder = true;
	config.fullScreen = false;
	config.resizable = false;
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
		}
		else {
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
	InputProcessor* inputProcessor;


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
		inputProcessor = Input::GetProcessor();
		if (inputProcessor != NULL) {
			inputProcessor->KeyDown(wParam);
		}
		break;
	case WM_KEYUP:
		inputProcessor = Input::GetProcessor();
		if (inputProcessor != NULL) {
			inputProcessor->KeyUp(wParam);
		}
		break;

	case WM_LBUTTONDOWN:
		inputProcessor = Input::GetProcessor();
		if (inputProcessor != NULL) {
			if (inputProcessor->TouchDown(LOWORD(lParam), HIWORD(lParam), KeyCode::Mouse_Left) == true) {
				mouseLeftBtnDown = true;
			}
		}
		break;
	case WM_LBUTTONUP:
		inputProcessor = Input::GetProcessor();
		if (inputProcessor != NULL) {
			if (mouseLeftBtnDown == true) {
				inputProcessor->TouchUp(LOWORD(lParam), HIWORD(lParam), KeyCode::Mouse_Left);				
			}						
		}
		mouseLeftBtnDown = false;
		break;
	case WM_MBUTTONDOWN:
		inputProcessor = Input::GetProcessor();
		if (inputProcessor != NULL) {
			if (inputProcessor->TouchDown(LOWORD(lParam), HIWORD(lParam), KeyCode::Mouse_Mid) == true) {
				mouseMidBtnDown = true;
			}
		}
		break;
	case WM_MBUTTONUP:
		inputProcessor = Input::GetProcessor();
		if (inputProcessor != NULL) {
			inputProcessor->TouchUp(LOWORD(lParam), HIWORD(lParam), KeyCode::Mouse_Mid);
		}
		mouseMidBtnDown = false;
		break;

	case WM_RBUTTONDOWN:
		inputProcessor = Input::GetProcessor();
		if (inputProcessor != NULL) {
			if (inputProcessor->TouchDown(LOWORD(lParam), HIWORD(lParam), KeyCode::Mouse_Right) == true) {
				mouseRightBtnDown = true;
			}
		}
		break;
	case WM_RBUTTONUP:
		inputProcessor = Input::GetProcessor();
		if (inputProcessor != NULL) {
			inputProcessor->TouchUp(LOWORD(lParam), HIWORD(lParam), KeyCode::Mouse_Right);
		}
		mouseRightBtnDown = false;
		break;
	case WM_MOUSEMOVE:
		inputProcessor = Input::GetProcessor();
		if (inputProcessor != NULL) {
			if (mouseLeftBtnDown) {
				inputProcessor->TouchDragged(LOWORD(lParam), HIWORD(lParam), KeyCode::Mouse_Left);
			}

			if (mouseMidBtnDown) {
				inputProcessor->TouchDragged(LOWORD(lParam), HIWORD(lParam), KeyCode::Mouse_Mid);
			}

			if (mouseRightBtnDown) {
				inputProcessor->TouchDragged(LOWORD(lParam), HIWORD(lParam), KeyCode::Mouse_Right);
			}			
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}