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
		Bool InitalizeWindow(const RenderConfig& config);        // 渲染窗口初始化
		void DestoryWindow();                             // 渲染窗口销毁

		void SetViewport(const Viewport& viewport);       // 设置视口
		Viewport GetViewport();                           // 返回视口

		void Clear(const Color& color);             // 清屏 
		void Flush();                               // 刷新缓冲区
		void SwapBuffer();                          // 交换缓冲区

		void SetPointSize(Float size);       // 设置点的大小
		Float GetPointSize();                // 返回点的大小

		void SetLineWidth(Float width);      // 设置线的宽度
		Float GetLineWidth();                // 返回线宽

		void SetBrushColor(const Color& color);     // 设置画笔颜色
		Color GetBrushColor();                      // 返回画笔颜色
    
		void SetProjectionMatrix(const Matrix4& projectionMatrix);        // 设置投影矩阵
		Matrix4& GetProjectionMatrix();                                   // 返回投影矩阵

		void SetTransformMatrix(const Matrix4& transformMatrix);          // 设置变换矩阵
		Matrix4& GetTransformMatrix();                                    // 返回变换矩阵

		void EnableDepthTest();                            // 启用深度测试
		void DisableDepthTest();                           // 关闭深度测试

		void EnableStencilTest();                          // 启用模板测试
		void DisableStencilTest();                         // 关闭模板测试

		UInt AddTexture(Texture& texture);         // 添加纹理
		void DelTexture(UInt textureId);           // 删除纹理
		void EnableTexture(UInt textureId);        // 启动纹理，纹理为栈的形式储存，应对多重纹理
		void DisableTexture(UInt textureId);       // 关闭纹理

		UInt AddLight(Light& light);               // 添加灯光
		void DelLight(UInt light);                 // 删除灯光
		void EnableLight(UInt light);              // 开启灯光
		void DisableLight(UInt light);             // 关闭灯光

		void SetBlendMode(const BlendMode& blendMode);        // 设置混合模式
		BlendMode GetBlendMode();                             // 返回混合模式

		void CachePrimitivew(Primitivew primit);           // 缓存图元，利用顶点缓冲区
		void DrawPrimitivew(const Primitivew& primit);     // 绘制图元
    
		UInt AddShader(Shader& shader);            // 编译并添加Shader
		void DelShader(UInt  shaderId);            // 卸载shader
		void EnableShader(UInt shaderId);          // 启用shader
		void DisableShader(UInt shaderId);         // 关闭shader

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