#ifndef _Render_System_Interface_H__
#define _Render_System_Interface_H__

#include "DllApi.h"

#include <windows.h>

#include "Types.h"
#include "Color.h"
#include "Viewport.h"
#include "Matrix4.h"
#include "Texture.h"
#include "Light.h"
#include "BlendMode.h"
#include "RenderObject.h"
#include "Shader.h"

namespace Soft3D{

struct DLLAPI RenderConfig{
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

class DLLAPI RenderSystemInterface{
public:
    virtual Bool InitalizeWindow(const RenderConfig& config) = 0;    // ��Ⱦ���ڳ�ʼ��
    virtual void DestoryWindow() = 0;                         // ��Ⱦ��������

	virtual void OnChangeSize(UInt width, UInt height) = 0;   // ���ڴ�С�ı�


    virtual void SetViewport(const Viewport& viewport) = 0;   // �����ӿ�
    virtual Viewport GetViewport() = 0;                       // �����ӿ�

    virtual void Clear(const Color& color) = 0;         // ���� 
    virtual void Flush() = 0;                           // ˢ�»�����
    virtual void SwapBuffer() = 0;                      // ����������

    virtual void SetPointSize(Float size) = 0;   // ���õ�Ĵ�С
    virtual Float GetPointSize() = 0;            // ���ص�Ĵ�С

    virtual void SetLineWidth(Float width) = 0;  // �����ߵĿ��
    virtual Float GetLineWidth() = 0;                // �����߿�

    virtual void SetBrushColor(const Color& color) = 0; // ���û�����ɫ
    virtual Color GetBrushColor() = 0;                  // ���ػ�����ɫ

	virtual void SetCombinedMatrix(Matrix4& combined) = 0;          // ������Ͼ���ΪͶӰ����
	virtual void PushTransformMatrix(Matrix4& transformMatrix) = 0; // ѹ��任����
	virtual void PopTransformMatrix() = 0;                          // �����任����

    virtual void EnableDepthTest() = 0;                        // ������Ȳ���
    virtual void DisableDepthTest() = 0;                       // �ر���Ȳ���

    virtual void EnableStencilTest() = 0;                      // ����ģ�����
    virtual void DisableStencilTest() = 0;                     // �ر�ģ�����

    virtual UInt AddTexture(Texture& texture) = 0;     // �������
    virtual void DelTexture(UInt textureId) = 0;       // ɾ������
    virtual void EnableTexture(UInt textureId) = 0;    // ������������Ϊջ����ʽ���棬Ӧ�Զ�������
    virtual void DisableTexture(UInt textureId) = 0;   // �ر�����

    virtual UInt AddLight(Light& light) = 0;           // ��ӵƹ�
    virtual void DelLight(UInt light) = 0;             // ɾ���ƹ�
    virtual void EnableLight(UInt light) = 0;          // �����ƹ�
    virtual void DisableLight(UInt light) = 0;         // �رյƹ�

	virtual void EnableBlend() = 0;                    // ���û��
	virtual void DisableBlend() = 0;                   // �رջ��
    virtual void SetBlendMode(const BlendMode& blendMode) = 0;    // ���û��ģʽ
    virtual BlendMode GetBlendMode() = 0;                         // ���ػ��ģʽ

    virtual void CacheRenderData(RenderData& renderData) = 0;       // ������Ⱦ����
    virtual void DrawRenderObject(RenderObject& renderObject) = 0; // ������Ⱦ����
    
    virtual UInt AddShader(Shader& shader) = 0;        // ���벢���Shader
    virtual void DelShader(UInt  shaderId) = 0;        // ж��shader
    virtual void EnableShader(UInt shaderId) = 0;      // ����shader
    virtual void DisableShader(UInt shaderId) = 0;     // �ر�shader

};

}


#endif