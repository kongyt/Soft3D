#include "RenderSystem_GL.h"
namespace Soft3D{

	Bool RenderSystemGL::InitalizeWindow(const RenderConfig& config){

		WNDCLASSEX wndClass = {0};
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = config.wndProc;
		wndClass.hInstance = config.hInstance;
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = config.title;

		if(!RegisterClassEx(&wndClass)){
			return false;
		}
	
		RECT rc = {0, 0, config.width, config.height};
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

		HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, config.title, config.title, WS_OVERLAPPEDWINDOW, 0, 0, rc.right-rc.left, rc.bottom-rc.top, NULL, NULL, config.hInstance, NULL); 

		if(!hwnd){
			return false;
		} 
		
	
		

		HGLRC hRC;	// opengl 绘制环境
		m_HDC = GetDC(hwnd);
		SetupPixelFormat(m_HDC);
		hRC = wglCreateContext(m_HDC); // 创建OpenGL绘制环境并创建一个指向OpenGL绘制环境的句柄
		wglMakeCurrent(m_HDC, hRC);

		ShowWindow(hwnd, SW_NORMAL);
		UpdateWindow(hwnd);

		InitGL();
	
		this->m_hInstance = config.hInstance;
		this->m_hWnd = hwnd;
		
		return true;
	}

	void RenderSystemGL::SetupPixelFormat(HDC hDC) { // 为设备环境设置像素格式
		int nPixelFormat;
		static PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0, // 忽略颜色，不使用
			0, // 无alpha缓存
			0, // 忽略偏移位
			0, // 无累积缓存
			0, 0, 0, 0, // 忽略累积位
			16, // 16位z-buffer大小
			0, // 无模板缓存
			0, // 无辅助缓存
			PFD_MAIN_PLANE, // 主绘制平面
			0, // 保留数据项
			0, 0, 0 // 忽略层面掩模
		};
		// 选择最匹配的像素格式，返回索引值
		nPixelFormat = ChoosePixelFormat(hDC, &pfd);

		// 设置环境设备的像素格式
		SetPixelFormat(hDC, nPixelFormat, &pfd);	
	}

	void RenderSystemGL::InitGL() {
		glShadeModel(GL_SMOOTH);		// 启动阴影平滑
		glClearDepth(1.0f);				// 设置深度缓存		
		glDepthFunc(GL_LEQUAL);			// 深度测试类型
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // 对透视进行修正

	}

	void RenderSystemGL::DestoryWindow(){
		
	}

	void RenderSystemGL::SetViewport(const Viewport& viewport){
	
	}

	Viewport RenderSystemGL::GetViewport(){
		return Viewport();
	}

	void RenderSystemGL::Clear(const Color& color){
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void RenderSystemGL::Flush(){
		glFlush();
	}

	void RenderSystemGL::SwapBuffer(){
		SwapBuffers(m_HDC);
	}

	void RenderSystemGL::SetPointSize(Float size){
		m_pointSize = size;
		glPointSize(size);
	}

	Float RenderSystemGL::GetPointSize(){
		return m_pointSize;
	}

	void RenderSystemGL::SetLineWidth(Float width){
		m_lineWidth = width;
		glLineWidth(width);
	}

	Float RenderSystemGL::GetLineWidth(){
		return m_lineWidth;
	}

	void RenderSystemGL::SetBrushColor(const Color& color){
		m_brushColor.r = color.r;
		m_brushColor.g = color.g;
		m_brushColor.b = color.b;
		m_brushColor.a = color.a;
	}

	Color RenderSystemGL::GetBrushColor(){
		return m_brushColor;
	}
    
	void RenderSystemGL::SetProjectionMatrix(const Matrix4& projectionMatrix){
		m_projectionMatrix.CopyData(projectionMatrix);
	}

	Matrix4& RenderSystemGL::GetProjectionMatrix(){
		return m_projectionMatrix;
	}

	void RenderSystemGL::SetTransformMatrix(const Matrix4& transformMatrix){
		m_transformMatrix.Add(transformMatrix);
	}

	Matrix4& RenderSystemGL::GetTransformMatrix(){
		return m_transformMatrix;
	}

	void RenderSystemGL::EnableDepthTest(){
		glEnable(GL_DEPTH_TEST);		// 启用深度测试
	}

	void RenderSystemGL::DisableDepthTest(){
		glDisable(GL_DEPTH_TEST);
	}

	void RenderSystemGL::EnableStencilTest(){
		glEnable(GL_STENCIL_TEST);
	}

	void RenderSystemGL::DisableStencilTest(){
		glDisable(GL_STENCIL_TEST);
	}
	
	UInt RenderSystemGL::AddTexture(Texture& texture){
		return 0;
	}

	void RenderSystemGL::DelTexture(UInt textureId){
	
	}

	void RenderSystemGL::EnableTexture(UInt textureId){
	
	}

	void RenderSystemGL::DisableTexture(UInt textureId){
	
	}

	UInt RenderSystemGL::AddLight(Light& light){
		return 0;
	}

	void RenderSystemGL::DelLight(UInt light){
	
	}

	void RenderSystemGL::EnableLight(UInt light){
	
	}

	void RenderSystemGL::DisableLight(UInt light){
	
	}

	void RenderSystemGL::SetBlendMode(const BlendMode& blendMode){
	
	}

	BlendMode RenderSystemGL::GetBlendMode(){
		return BlendMode();
	}

	void RenderSystemGL::CachePrimitivew(Primitivew primit){
	
	}

	void RenderSystemGL::DrawPrimitivew(const Primitivew& primit){
	
	}
    
	UInt RenderSystemGL::AddShader(Shader& shader){
		return 0;
	}

	void RenderSystemGL::DelShader(UInt  shaderId){
	
	}

	void RenderSystemGL::EnableShader(UInt shaderId){
	
	}

	void RenderSystemGL::DisableShader(UInt shaderId){
	
	}

}
