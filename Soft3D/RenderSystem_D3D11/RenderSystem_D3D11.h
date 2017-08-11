#ifndef _Render_System_D3D11_H__
#define _Render_System_D3D11_H__

#include "../Soft3D/DllApi.h"
#include "../Soft3D/RenderSystemInterface.h"

namespace Soft3D{

	class DLLAPI RenderSystemD3D11: public RenderSystemInterface{
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
    
		void SetProjectionMatrix(const Matrix4& projectionMatrix);        // 设置投影矩阵
		Matrix4& GetProjectionMatrix();                                   // 返回投影矩阵

		virtual void SetModelViewMatrix(const Matrix4& viewMatrix) = 0;      // 设置模型视图矩阵
		virtual Matrix4& GetModelViewMatrix() = 0;                           // 返回模型视图矩阵

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
	
	};

}

#endif