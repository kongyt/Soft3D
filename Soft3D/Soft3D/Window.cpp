#include <time.h>
#include "Window.h"

namespace Soft3D {

	Bool Window::Initalize(Game* game, const WindowConfig& config) {
		this->m_Game = game;
		this->windowConfig = config;

		Int x = config.fullScreen ? 0 : config.x;
		Int y = config.fullScreen ? 0 : config.y;
		Int width = config.fullScreen ? GetSystemMetrics(SM_CXSCREEN) : config.width;
		Int height = config.fullScreen ? GetSystemMetrics(SM_CYSCREEN) : config.height;
		Bool hasBorder = config.fullScreen ? false : config.hasBorder;

		WNDCLASSEX wndClass = { 0 };
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = config.wndProc;
		wndClass.hInstance = config.hInstance;
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = config.title;

		if (!RegisterClassEx(&wndClass)) {
			return false;
		}

		HWND hwnd;

		if (hasBorder) {
			RECT rc = { x, y, x + width, y + height };
			AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

			hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, config.title, config.title, WS_OVERLAPPEDWINDOW, x, y, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, config.hInstance, NULL);
		}
		else {
			hwnd = CreateWindowEx(NULL, config.title, config.title, WS_POPUP | WS_VISIBLE, x, y, width, height, NULL, NULL, config.hInstance, NULL);
		}

		if (!hwnd) {
			return false;
		}

		
		bool ret = renderContext.Init(hwnd);

		if (ret == false) {
			return false;
		}

		if (config.fullScreen == false) {
			glViewport(0, 0, config.width, config.height);
		}
		else {
			glViewport(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		}
		
		m_Game->SetSize(windowConfig.width, windowConfig.height);
		m_Game->Start();


		ShowWindow(hwnd, SW_NORMAL);
		UpdateWindow(hwnd);

		t1 = clock();
		return true;
	}


	void Window::Render() {
		t2 = clock();
		m_delta = (t2 - t1) / 1000.0f;
		t1 = t2;
		m_Game->Render(renderContext, m_delta);

		renderContext.SwapBuffer();	// ½»»»»º³åÇø
	}


	void Window::Destory() {
		m_Game->Destroy();
		renderContext.Destroy();
	}

	void Window::OnChangeSize(UInt width, UInt height) {
		glViewport(0, 0, width, height);
		m_Game->SetSize(width, height);
	}

	RenderContext& Window::GetRenderContext() {
		return renderContext;
	}
}