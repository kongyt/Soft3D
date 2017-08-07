#ifndef _Render_System_D3D11_H__
#define _Render_System_D3D11_H__

#include "../Soft3D/RenderSystemInterface.h"

namespace Soft3D{

	class RenderSystemD3D11: public RenderSystemInterface{
	public:
	Bool InitalizeWindow(RenderConfig config);        // ��Ⱦ���ڳ�ʼ��
    void Render();                                    // ��Ⱦ֡
    void DestoryWindow();                             // ��Ⱦ��������

    void SetViewport(const Viewport& viewport);       // �����ӿ�
    Viewport GetViewport();                           // �����ӿ�

    void Clear(const Color& color);             // ���� 
    void Flush();                               // ˢ�»�����
    void SwapBuffer();                          // ����������

    void SetPointSize(UInt size);       // ���õ�Ĵ�С
    UInt GetPointSize();                // ���ص�Ĵ�С

    void SetLineWidth(UInt width);      // �����ߵĿ��
    UInt GetLineWidth();                    // �����߿�

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
	
	};

}

#endif