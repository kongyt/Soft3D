#ifndef _Window_H__
#define _Window_H__

#include <Windows.h>
#include <time.h>

#include "GLES_Support.h"

#include "DllApi.h"
#include "Types.h"
#include "RenderContext.h"
#include "Game.h"


namespace Soft3D {

	struct DLLAPI WindowConfig {
		HINSTANCE hInstance;        // ����ʵ��
		TCHAR*    title;            // ����
		Bool      fullScreen;       // �Ƿ�ȫ��
		Bool      hasBorder;        // �Ƿ��б߿�
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

		RenderContext& GetRenderContext();
	private:
		WindowConfig windowConfig;
		RenderContext renderContext;

		Game* m_Game;
		clock_t t1;
		clock_t t2;
		Float m_delta;

	};


}

#endif