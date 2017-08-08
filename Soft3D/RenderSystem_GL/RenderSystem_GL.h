#ifndef _Render_System_GL_H__
#define _Render_System_GL_H__

#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")

#include "../Soft3D/DllApi.h"
#include "../Soft3D/RenderSystemInterface.h"

namespace Soft3D{

	class DLLAPI RenderSystemGL: public RenderSystemInterface{
	public:
		Bool InitalizeWindow(const RenderConfig& config);        // ��Ⱦ���ڳ�ʼ��
		void DestoryWindow();                             // ��Ⱦ��������

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
    
		void SetProjectionMatrix(const Matrix4& projectionMatrix);        // ����ͶӰ����
		Matrix4& GetProjectionMatrix();                                   // ����ͶӰ����

		void SetTransformMatrix(const Matrix4& transformMatrix);          // ���ñ任����
		Matrix4& GetTransformMatrix();                                    // ���ر任����

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

		void SetBlendMode(const BlendMode& blendMode);        // ���û��ģʽ
		BlendMode GetBlendMode();                             // ���ػ��ģʽ

		void CachePrimitivew(Primitivew primit);           // ����ͼԪ�����ö��㻺����
		void DrawPrimitivew(const Primitivew& primit);     // ����ͼԪ
    
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
		Color     m_brushColor;
		Matrix4   m_projectionMatrix;
		Matrix4   m_transformMatrix;
		Float     m_pointSize;
		Float     m_lineWidth;
	};

}

#endif