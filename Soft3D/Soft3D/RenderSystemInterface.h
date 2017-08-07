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
	HINSTANCE hInstance;        // 程序实例
	Bool      fullScreen;       // 是否全屏
	UInt      width;            // 非全屏时窗口客户区宽度
	UInt      height;           // 非全屏时窗口客户区高度
	WNDPROC   wndProc;          // 消息处理函数
};

class RenderSystemInterface{
public:
    virtual Bool InitalizeWindow(RenderConfig config) = 0;    // 渲染窗口初始化
    virtual void Render() = 0;                                // 渲染帧
    virtual void DestoryWindow() = 0;                         // 渲染窗口销毁

    virtual void SetViewport(const Viewport& viewport) = 0;   // 设置视口
    virtual Viewport GetViewport() = 0;                       // 返回视口

    virtual void Clear(const Color& color) = 0;         // 清屏 
    virtual void Flush() = 0;                           // 刷新缓冲区
    virtual void SwapBuffer() = 0;                      // 交换缓冲区

    virtual void SetPointSize(UInt size) = 0;   // 设置点的大小
    virtual UInt GetPointSize() = 0;            // 返回点的大小

    virtual void SetLineWidth(UInt width) = 0;  // 设置线的宽度
    virtual UInt GetLineWidth() = 0;                // 返回线宽

    virtual void SetBrushColor(const Color& color) = 0; // 设置画笔颜色
    virtual Color GetBrushColor() = 0;                  // 返回画笔颜色
    
    virtual void SetProjectionMatrix(const Matrix4& projectionMatrix) = 0;    // 设置投影矩阵
    virtual Matrix4& GetProjectionMatrix() = 0;                               // 返回投影矩阵

    virtual void SetTransformMatrix(const Matrix4& transformMatrix) = 0;      // 设置变换矩阵
    virtual Matrix4& GetTransformMatrix() = 0;                                // 返回变换矩阵

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