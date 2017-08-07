#ifndef _Render_System_Interface_H__
#define _Render_System_Interface_H__

#include <windows.h>

#include "Types.h"

namespace Soft3D{

class Color;
class Vector3f;
class Shader;
class Matrix4;
class Light;
class Texture;
class BlendMode;
class Primitivew;
class Viewport;

struct RenderConfig{
	HINSTANCE hInstance;        // ����ʵ��
	Bool      fullScreen;       // �Ƿ�ȫ��
	UInt      width;            // ��ȫ��ʱ���ڿͻ������
	UInt      height;           // ��ȫ��ʱ���ڿͻ����߶�
	WNDPROC   wndProc;          // ��Ϣ������
};

class RenderSystemInterface{
public:
    virtual Bool InitalizeWindow(RenderConfig config) = 0;    // ��Ⱦ���ڳ�ʼ��
    virtual void Render() = 0;                                // ��Ⱦ֡
    virtual void DestoryWindow() = 0;                         // ��Ⱦ��������

    virtual void SetViewport(const Viewport& viewport) = 0;   // �����ӿ�
    virtual Viewport GetViewport() = 0;                       // �����ӿ�

    virtual void Clear(const Color& color) = 0;         // ���� 
    virtual void Flush() = 0;                           // ˢ�»�����
    virtual void SwapBuffer() = 0;                      // ����������

    virtual void SetPointSize(UInt size) = 0;   // ���õ�Ĵ�С
    virtual UInt GetPointSize() = 0;            // ���ص�Ĵ�С

    virtual void SetLineWidth(UInt width) = 0;  // �����ߵĿ��
    virtual UInt GetLineWidth() = 0;                // �����߿�

    virtual void SetBrushColor(const Color& color) = 0; // ���û�����ɫ
    virtual Color GetBrushColor() = 0;                  // ���ػ�����ɫ
    
    virtual void SetProjectionMatrix(const Matrix4& projectionMatrix) = 0;    // ����ͶӰ����
    virtual Matrix4& GetProjectionMatrix() = 0;                               // ����ͶӰ����

    virtual void SetTransformMatrix(const Matrix4& transformMatrix) = 0;      // ���ñ任����
    virtual Matrix4& GetTransformMatrix() = 0;                                // ���ر任����

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

    virtual void SetBlendMode(const BlendMode& blendMode) = 0;    // ���û��ģʽ
    virtual BlendMode GetBlendMode() = 0;                         // ���ػ��ģʽ

    virtual void CachePrimitivew(Primitivew primit) = 0;       // ����ͼԪ�����ö��㻺����
    virtual void DrawPrimitivew(const Primitivew& primit) = 0; // ����ͼԪ
    
    virtual UInt AddShader(Shader& shader) = 0;        // ���벢���Shader
    virtual void DelShader(UInt  shaderId) = 0;        // ж��shader
    virtual void EnableShader(UInt shaderId) = 0;      // ����shader
    virtual void DisableShader(UInt shaderId) = 0;     // �ر�shader

};

}


#endif