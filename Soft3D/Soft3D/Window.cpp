#include <time.h>
#include "Window.h"
#include <stdio.h>

namespace Soft3D {

	Bool Window::Initalize(Game* game, const WindowConfig& config) {
		this->m_Game = game;

		Int x = config.fullScreen ? 0 : config.x;
		Int y = config.fullScreen ? 0 : config.y;
		Int width = config.fullScreen ? GetSystemMetrics(SM_CXSCREEN) : config.width;
		Int height = config.fullScreen ? GetSystemMetrics(SM_CYSCREEN) : config.height;
		Bool hasBorder = config.fullScreen ? false : config.hasBorder;
		Bool resizable = config.fullScreen ? false : config.resizable;

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

			if (resizable) {
				hwnd = CreateWindowEx(NULL, config.title, config.title, WS_OVERLAPPEDWINDOW, x, y, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, config.hInstance, NULL);
			}
			else {
				hwnd = CreateWindowEx(NULL, config.title, config.title, WS_OVERLAPPEDWINDOW^WS_THICKFRAME, x, y, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, config.hInstance, NULL);
			}		
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
		
		UpdateWindow(hwnd);
		ShowWindow(hwnd, SW_NORMAL);
		

		m_Game->SetSize(width, height);
		m_Game->Start();		

		t1 = clock();
		m_initialized = true;
		return true;
	}

	int fps = 0;

	void Window::Render() {
		t2 = clock();
		m_delta = (t2 - t1) / 1000.0f;
		t1 = t2;
		fps = 1 / m_delta;
		//printf("fps:%d\n", fps);
		renderContext.Begin();
		m_Game->Render(renderContext, m_delta);
		renderContext.End();
	}


	void Window::Destory() {
		m_Game->Destroy();
		renderContext.Destroy();
	}

	void Window::OnChangeSize(UInt width, UInt height) {
		if (m_initialized) {
			glViewport(0, 0, width, height);
			m_Game->SetSize(width, height);
		}		
	}

	RenderContext& Window::GetRenderContext() {
		return renderContext;
	}

	void Window::Exit(){
		PostQuitMessage(0);
	}
}