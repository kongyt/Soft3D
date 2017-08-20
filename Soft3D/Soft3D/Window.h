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
		HINSTANCE hInstance;        // ����ʵ��
		TCHAR*    title;            // ����
		Bool      fullScreen = false;       // �Ƿ�ȫ��
		Bool      hasBorder = false;        // �Ƿ��б߿�
		Bool      resizable = true;        // �Ƿ�ɸı��С
		Int       x;                // ���Ͻ�x����
		Int       y;                // ���Ͻ�y����
		Long      width;            // ��ȫ��ʱ���ڿͻ������
		Long      height;           // ��ȫ��ʱ���ڿͻ����߶�
		WNDPROC   wndProc;          // ��Ϣ������
	};

	class DLLAPI Window {
	public:
		Bool Initalize(Game* game, const WindowConfig& config); // ��Ⱦ���ڳ�ʼ��
		void Render();
		void Destory();                             // ��Ⱦ��������
		void OnChangeSize(UInt width, UInt height);       // ���ڴ�С�ı�

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