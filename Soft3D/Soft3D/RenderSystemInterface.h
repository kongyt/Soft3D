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
#include "Primitivew.h"
#include "Shader.h"

namespace Soft3D{

struct DLLAPI RenderConfig{
	HINSTANCE hInstance;        // 程序实例
	TCHAR*    title;            // 标题
	Bool      fullScreen;       // 是否全屏
	Bool      hasBorder;        // 是否有边框
	Int       x;                // 左上角x坐标
	Int       y;                // 左上角y坐标
	Long      width;            // 非全屏时窗口客户区宽度
	Long      height;           // 非全屏时窗口客户区高度
	WNDPROC   wndProc;          // 消息处理函数
};

class DLLAPI RenderSystemInterface{
public:
    virtual Bool InitalizeWindow(const RenderConfig& config) = 0;    // 渲染窗口初始化
    virtual void DestoryWindow() = 0;                         // 渲染窗口销毁

	virtual void OnChangeSize(UInt width, UInt height) = 0;   // 窗口大小改变


    virtual void SetViewport(const Viewport& viewport) = 0;   // 设置视口
    virtual Viewport GetViewport() = 0;                       // 返回视口

    virtual void Clear(const Color& color) = 0;         // 清屏 
    virtual void Flush() = 0;                           // 刷新缓冲区
    virtual void SwapBuffer() = 0;                      // 交换缓冲区

    virtual void SetPointSize(Float size) = 0;   // 设置点的大小
    virtual Float GetPointSize() = 0;            // 返回点的大小

    virtual void SetLineWidth(Float width) = 0;  // 设置线的宽度
    virtual Float GetLineWidth() = 0;                // 返回线宽

    virtual void SetBrushColor(const Color& color) = 0; // 设置画笔颜色
    virtual Color GetBrushColor() = 0;                  // 返回画笔颜色
    
    virtual void SetProjectionMatrix(const Matrix4& projectionMatrix) = 0;    // 设置投影矩阵
    virtual Matrix4& GetProjectionMatrix() = 0;                               // 返回投影矩阵

    virtual void SetModelViewMatrix(const Matrix4& viewMatrix) = 0;      // 设置变换矩阵
    virtual Matrix4& GetModelViewMatrix() = 0;                                // 返回变换矩阵

    virtual void EnableDepthTest() = 0;                        // 启用深度测试
    virtual void DisableDepthTest() = 0;                       // 关闭深度测试

    virtual void EnableStencilTest() = 0;                      // 启用模板测试
    virtual void DisableStencilTest() = 0;                     // 关闭模板测试

    virtual UInt AddTexture(Texture& texture) = 0;     // 添加纹理
    virtual void DelTexture(UInt textureId) = 0;       // 删除纹理
    virtual void EnableTexture(UInt textureId) = 0;    // 启动纹理，纹理为栈的形式储存，应对多重纹理
    virtual void DisableTexture(UInt textureId) = 0;   // 关闭纹理

    virtual UInt AddLight(Light& light) = 0;           // 添加灯光
    virtual void DelLight(UInt light) = 0;             // 删除灯光
    virtual void EnableLight(UInt light) = 0;          // 开启灯光
    virtual void DisableLight(UInt light) = 0;         // 关闭灯光

	virtual void EnableBlend() = 0;                    // 启用混合
	virtual void DisableBlend() = 0;                   // 关闭混合
    virtual void SetBlendMode(const BlendMode& blendMode) = 0;    // 设置混合模式
    virtual BlendMode GetBlendMode() = 0;                         // 返回混合模式

    virtual void CachePrimitivew(Primitivew primit) = 0;       // 缓存图元，利用顶点缓冲区
    virtual void DrawPrimitivew(const Primitivew& primit) = 0; // 绘制图元
    
    virtual UInt AddShader(Shader& shader) = 0;        // 编译并添加Shader
    virtual void DelShader(UInt  shaderId) = 0;        // 卸载shader
    virtual void EnableShader(UInt shaderId) = 0;      // 启用shader
    virtual void DisableShader(UInt shaderId) = 0;     // 关闭shader

};

}


#endif