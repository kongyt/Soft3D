#include "RenderSystem_GL.h"
namespace Soft3D{

	Bool RenderSystemGL::InitalizeWindow(const RenderConfig& config){

		Int x = config.fullScreen ? 0 : config.x;
		Int y = config.fullScreen ? 0 : config.y;
		Int width = config.fullScreen ? GetSystemMetrics(SM_CXSCREEN) : config.width;
		Int height = config.fullScreen ? GetSystemMetrics(SM_CYSCREEN) : config.height;
		Bool hasBorder = config.fullScreen ? false : config.hasBorder;		

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

		HWND hwnd;
	
		if (hasBorder) {
			RECT rc = { x, y, x+width, y+height };
			AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

			hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, config.title, config.title, WS_OVERLAPPEDWINDOW, x, y, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, config.hInstance, NULL);			
		}
		else {
			hwnd = CreateWindowEx(NULL, config.title, config.title, WS_POPUP | WS_VISIBLE, x, y, width, height, NULL, NULL, config.hInstance, NULL);
		}
		
		if (!hwnd) {
			return false;
		}
		
		m_HDC = GetDC(hwnd);
		SetupPixelFormat(m_HDC);
		m_HRC = wglCreateContext(m_HDC); // ����OpenGL���ƻ���������һ��ָ��OpenGL���ƻ����ľ��
		wglMakeCurrent(m_HDC, m_HRC);

		if (config.fullScreen == false) {
			SetViewport(Viewport(0, 0, config.width, config.height));
		}
		else {
			SetViewport(Viewport(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));
		}

		InitGL();

		ShowWindow(hwnd, SW_NORMAL);
		UpdateWindow(hwnd);
		
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
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_HRC);
		ReleaseDC(m_hWnd, m_HDC);

		// destroy the window explicitly
		DestroyWindow(m_hWnd);
	}

	void RenderSystemGL::OnChangeSize(UInt width, UInt height) {
		SetViewport(Viewport(0, 0, width, height));
	}

	void RenderSystemGL::SetViewport(const Viewport& viewport){
		m_Viewport.x = viewport.x;
		m_Viewport.y = viewport.y;
		m_Viewport.width = viewport.width;
		m_Viewport.height = viewport.height;

		glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
	}

	Viewport RenderSystemGL::GetViewport(){
		return m_Viewport;
	}

	void RenderSystemGL::Clear(const Color& color){
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BITS);

		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0, 0.0f, -1000.0f);

		glColor3f(0.0f, 1.0f, 0.0f); 
		glVertex3f(400, 0.0f, -1000.0f);

		glColor3f(0.0f, 0.0f, 1.0f); 
		glVertex3f(400, 240, -1000.0f);

		glEnd();
		glPopMatrix();
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
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(projectionMatrix.data);
	}

	Matrix4& RenderSystemGL::GetProjectionMatrix(){
		return m_projectionMatrix;
	}

	void RenderSystemGL::SetModelViewMatrix(const Matrix4& viewMatrix){
		m_viewMatrix.CopyData(viewMatrix);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(viewMatrix.data);
	}

	Matrix4& RenderSystemGL::GetModelViewMatrix(){
		return m_viewMatrix;
	}

	void RenderSystemGL::EnableDepthTest(){
		m_usedDepthTest = true;
		glEnable(GL_DEPTH_TEST);		// ������Ȳ���
	}

	void RenderSystemGL::DisableDepthTest(){
		m_usedDepthTest = false;
		glDisable(GL_DEPTH_TEST);
	}

	void RenderSystemGL::EnableStencilTest(){
		m_usedStencilTest = true;
		glEnable(GL_STENCIL_TEST);
	}

	void RenderSystemGL::DisableStencilTest(){
		m_usedStencilTest = false;
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

	void RenderSystemGL::EnableBlend() {
		m_usedBlend = true;
		glEnable(GL_BLEND);
	}

	void RenderSystemGL::DisableBlend() {
		m_usedBlend = false;
		glDisable(GL_BLEND);
	}

	GLenum GetBlendType(const Blend& blend) {
		GLenum rs = GL_ZERO;
		switch (blend)
		{
		case Blend::Zero:
			rs = GL_ZERO;
			break;
		case Blend::One:
			rs = GL_ONE;
			break;
		case Blend::Src_Color:
			rs = GL_SRC_COLOR;
			break;
		case Blend::One_Minus_Src_Color:
			rs = GL_ONE_MINUS_SRC_COLOR;
			break;
		case Blend::Dst_Color:
			rs = GL_DST_COLOR;
			break;
		case Blend::One_Minus_Dst_Color:
			rs = GL_ONE_MINUS_DST_COLOR;
			break;
		case Blend::Src_Alpha:
			rs = GL_SRC_ALPHA;
			break;
		case Blend::One_Minus_Src_Alpha:
			rs = GL_ONE_MINUS_SRC_ALPHA;
			break;
		case Blend::Dst_Alpha:
			rs = GL_DST_ALPHA;
			break;
		case Blend::One_Minus_Dst_Alpha:
			rs = GL_ONE_MINUS_DST_ALPHA;
			break;
		case Blend::Src_Alpha_Saturate:
			rs = GL_SRC_ALPHA_SATURATE;
			break;
		default:
			exit(-1000);
			break;
		}
		return rs;
	}

	void RenderSystemGL::SetBlendMode(const BlendMode& blendMode){
		m_blendMode.srcBlend = blendMode.srcBlend;
		m_blendMode.dstBlend = blendMode.dstBlend;
		glBlendFunc(GetBlendType(blendMode.srcBlend), GetBlendType(blendMode.dstBlend));
	}

	BlendMode RenderSystemGL::GetBlendMode(){
		return m_blendMode;
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
