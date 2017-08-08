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
		
	
		

		HGLRC hRC;	// opengl ���ƻ���
		m_HDC = GetDC(hwnd);
		SetupPixelFormat(m_HDC);
		hRC = wglCreateContext(m_HDC); // ����OpenGL���ƻ���������һ��ָ��OpenGL���ƻ����ľ��
		wglMakeCurrent(m_HDC, hRC);

		ShowWindow(hwnd, SW_NORMAL);
		UpdateWindow(hwnd);

		InitGL();
	
		this->m_hInstance = config.hInstance;
		this->m_hWnd = hwnd;
		
		return true;
	}

	void RenderSystemGL::SetupPixelFormat(HDC hDC) { // Ϊ�豸�����������ظ�ʽ
		int nPixelFormat;
		static PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0, // ������ɫ����ʹ��
			0, // ��alpha����
			0, // ����ƫ��λ
			0, // ���ۻ�����
			0, 0, 0, 0, // �����ۻ�λ
			16, // 16λz-buffer��С
			0, // ��ģ�建��
			0, // �޸�������
			PFD_MAIN_PLANE, // ������ƽ��
			0, // ����������
			0, 0, 0 // ���Բ�����ģ
		};
		// ѡ����ƥ������ظ�ʽ����������ֵ
		nPixelFormat = ChoosePixelFormat(hDC, &pfd);

		// ���û����豸�����ظ�ʽ
		SetPixelFormat(hDC, nPixelFormat, &pfd);	
	}

	void RenderSystemGL::InitGL() {
		glShadeModel(GL_SMOOTH);		// ������Ӱƽ��
		glClearDepth(1.0f);				// ������Ȼ���		
		glDepthFunc(GL_LEQUAL);			// ��Ȳ�������
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // ��͸�ӽ�������

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
		glEnable(GL_DEPTH_TEST);		// ������Ȳ���
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
