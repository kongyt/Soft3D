#ifndef _Render_System_GL_H__
#define _Render_System_GL_H__

#include <stack>

#include <Windows.h>
#include "../../3rd/glew-2.1.0/include/GL/glew.h"
#include <GL/GL.h>
#include <GL/GLU.h>

#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")

#include "../Soft3D/DllApi.h"
#include "../Soft3D/RenderSystemInterface.h"
#include "GLShaderManager.h"

namespace Soft3D{

	class DLLAPI RenderSystemGL: public RenderSystemInterface{
	public:
		Bool InitalizeWindow(const RenderConfig& config);        // ��Ⱦ���ڳ�ʼ��
		void DestoryWindow();                             // ��Ⱦ��������
		void OnChangeSize(UInt width, UInt height);       // ���ڴ�С�ı�

		void SetViewport(const Viewport& viewport);       // �����ӿ�
		Viewport GetViewport();                           // �����ӿ�

		void Clear(const Color& color);             // ���� 
		void Flush();                               // ˢ�»�����
		void SwapBuffer();                          // ����������

		void SetPointSize(Float size);       // ���õ�Ĵ�С
		Float GetPointSize();                // ���ص�Ĵ�С

		void SetLineWidth(Float width);      // �����ߵĿ��
		Float GetLineWidth();                // �����߿�

		void SetBrushColor(const Color& color);     // ���û�����ɫ
		Color GetBrushColor();                      // ���ػ�����ɫ

		void SetCombinedMatrix(Matrix4& combined);          // ����Camera��Combined����
		void PushTransformMatrix(Matrix4& transformMatrix); // ѹ��任����
		void PopTransformMatrix();                          // �����任����


		void EnableDepthTest();                            // ������Ȳ���
		void DisableDepthTest();                           // �ر���Ȳ���

		void EnableStencilTest();                          // ����ģ�����
		void DisableStencilTest();                         // �ر�ģ�����

		UInt AddTexture(Texture& texture);         // �������
		void DelTexture(UInt textureId);           // ɾ������
		void EnableTexture(UInt textureId);        // ������������Ϊջ����ʽ���棬Ӧ�Զ�������
		void DisableTexture(UInt textureId);       // �ر�����

		UInt AddLight(Light& light);               // ��ӵƹ�
		void DelLight(UInt light);                 // ɾ���ƹ�
		void EnableLight(UInt light);              // �����ƹ�
		void DisableLight(UInt light);             // �رյƹ�

		void EnableBlend();                        // ���û��
		void DisableBlend();                       // �رջ��
		void SetBlendMode(const BlendMode& blendMode);        // ���û��ģʽ
		BlendMode GetBlendMode();                             // ���ػ��ģʽ

		void CacheRenderData(RenderData& renderData);       // ������Ⱦ����
		void DrawRenderObject(RenderObject& renderObject); // ������Ⱦ����
    
		UInt AddShader(Shader& shader);            // ���벢���Shader
		void DelShader(UInt  shaderId);            // ж��shader
		void EnableShader(UInt shaderId);          // ����shader
		void DisableShader(UInt shaderId);         // �ر�shader

	private:
		void SetupPixelFormat(HDC hDC);
		void InitGL();
	private:
		HINSTANCE m_hInstance;
		HWND      m_hWnd;
		HDC       m_HDC;
		HGLRC     m_HRC;	// opengl ���ƻ���
		Viewport  m_Viewport = Viewport(0,0);
		Color     m_brushColor;
		
		Float     m_pointSize;
		Float     m_lineWidth;
		Bool      m_usedDepthTest;
		Bool      m_usedStencilTest;
		Bool      m_usedBlend;
		BlendMode m_blendMode;
		GLShaderManager m_glShaderManager;
		std::stack<Matrix4*> m_transMatrixStack;
		Matrix4   m_currentTransMatrix;

	};

}

#endif