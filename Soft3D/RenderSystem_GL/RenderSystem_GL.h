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
		Bool InitalizeWindow(const RenderConfig& config);        // 渲染窗口初始化
		void DestoryWindow();                             // 渲染窗口销毁
		void OnChangeSize(UInt width, UInt height);       // 窗口大小改变

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

		void SetCombinedMatrix(Matrix4& combined);          // 设置Camera的Combined矩阵
		void PushTransformMatrix(Matrix4& transformMatrix); // 压入变换矩阵
		void PopTransformMatrix();                          // 弹出变换矩阵


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

		void EnableBlend();                        // 启用混合
		void DisableBlend();                       // 关闭混合
		void SetBlendMode(const BlendMode& blendMode);        // 设置混合模式
		BlendMode GetBlendMode();                             // 返回混合模式

		void CacheRenderData(RenderData& renderData);       // 缓存渲染对象
		void DrawRenderObject(RenderObject& renderObject); // 绘制渲染对象
    
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
		HGLRC     m_HRC;	// opengl 绘制环境
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