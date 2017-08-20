#ifndef _Window_H__
#define _Window_H__

#include <Windows.h>
#include <time.h>

#include "GLES_Support.h"

#include "DllApi.h"
#include "Types.h"
#include "RenderContext.h"
#include "Game.h"
#include "InputProcessor.h"


namespace Soft3D {

	struct DLLAPI WindowConfig {
		HINSTANCE hInstance;        // 程序实例
		TCHAR*    title;            // 标题
		Bool      fullScreen = false;       // 是否全屏
		Bool      hasBorder = false;        // 是否有边框
		Bool      resizable = true;        // 是否可改变大小
		Int       x;                // 左上角x坐标
		Int       y;                // 左上角y坐标
		Long      width;            // 非全屏时窗口客户区宽度
		Long      height;           // 非全屏时窗口客户区高度
		WNDPROC   wndProc;          // 消息处理函数
	};

	class DLLAPI Window {
	public:
		Bool Initalize(Game* game, const WindowConfig& config); // 渲染窗口初始化
		void Render();
		void Destory();                             // 渲染窗口销毁
		void OnChangeSize(UInt width, UInt height);       // 窗口大小改变

		static void Exit();

		RenderContext& GetRenderContext();
	private:
		RenderContext renderContext;

		Game* m_Game;
		clock_t t1;
		clock_t t2;
		Float m_delta;
		Bool m_initialized = false;

	};


}

#endif