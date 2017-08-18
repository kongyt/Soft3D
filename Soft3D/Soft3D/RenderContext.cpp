#include "RenderContext.h"
#include "Shader.h"

namespace Soft3D {

	Bool RenderContext::Init(HWND hwnd) {
		//������egl ��ʾ����
		m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		if (m_eglDisplay == EGL_NO_DISPLAY)
		{
			return false;
		}

		//��ʼ����ȷ��egl�汾
		EGLint majorVersion;
		EGLint minorVersion;
		if (!eglInitialize(m_eglDisplay, &majorVersion, &minorVersion))
		{
			return false;
		}

		// ��ȡ֧�ֵ�egl����
		EGLint nConfigs;
		if (!eglGetConfigs(m_eglDisplay, NULL, 0, &nConfigs))
		{
			return false;
		}


		// �������õ���Щ���� ��������
		EGLint attrs[MAX_EGL_ATTRIBUTES] = { 0 };
		int attrIdx = 0;
		attrs[attrIdx++] = EGL_RED_SIZE;
		attrs[attrIdx++] = 5;
		attrs[attrIdx++] = EGL_GREEN_SIZE;
		attrs[attrIdx++] = 6;
		attrs[attrIdx++] = EGL_BLUE_SIZE;
		attrs[attrIdx++] = 5;
		attrs[attrIdx++] = EGL_ALPHA_SIZE;
		attrs[attrIdx++] = 0;
		attrs[attrIdx++] = EGL_DEPTH_SIZE;
		attrs[attrIdx++] = 16;
		attrs[attrIdx++] = EGL_STENCIL_SIZE;
		attrs[attrIdx++] = 0;
		attrs[attrIdx++] = EGL_SAMPLES;
		attrs[attrIdx++] = 4;
		attrs[attrIdx++] = EGL_NONE;
		if (!eglChooseConfig(m_eglDisplay, attrs, &m_eglConfig, 1, &nConfigs))
		{
			return false;
		}

		//�������ڱ�Ƥ ���� 
		m_eglSurface = eglCreateWindowSurface(
			m_eglDisplay, m_eglConfig, NativeWindowType(hwnd), NULL);
		if (m_eglSurface == EGL_NO_SURFACE)
		{
			return false;
		}

		//����egl������
		EGLint ctxAttr[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
		m_eglContext = eglCreateContext(m_eglDisplay, m_eglConfig, EGL_NO_CONTEXT, ctxAttr);
		if (m_eglContext == EGL_NO_CONTEXT)
		{
			return false;
		}

		//���� egl׼������ �Ժ󻭵Ķ�������egl������
		if (!eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext))
		{
			return false;
		}

		return true;
	}
	
	void RenderContext::Destroy() {
	
	}

	void RenderContext::SwapBuffer() {
		eglSwapBuffers(m_eglDisplay, m_eglSurface);
	}

	void RenderContext::SetCameraMatrix(Matrix4& cameraMatrix) {
		m_projectionMatrix.Set(cameraMatrix);
	}


	void RenderContext::PushTransformMatrix(Matrix4& transformMatrix) {
		Matrix4* tmp = m_transformMatrix.Clone();
		m_transMatrixStack.push(tmp);

		m_transformMatrix.Mul(transformMatrix);
		m_combinedMatrix.Set(m_projectionMatrix).Mul(m_transformMatrix);
	}


	void RenderContext::PopTransformMatrix() {
		if (m_transMatrixStack.size() > 0) {
			m_transformMatrix.Set(*m_transMatrixStack.top());
			delete m_transMatrixStack.top();
			m_transMatrixStack.pop();
		}
		else {
			m_transformMatrix.Identity();
		}
		m_combinedMatrix.Set(m_projectionMatrix).Mul(m_transformMatrix);
	}

	Matrix4& RenderContext::GetCombinedMatrix() {
		return m_combinedMatrix;
	}

	Shader* RenderContext::GetDefaultShader() {
		if (m_defaultShader == NULL) {
			const char* vertexShader =
				"attribute vec4 " POSITION_ATTRIBUTE ";\n"
				"attribute vec4 " COLOR_ATTRIBUTE ";\n"
				"attribute vec2 " TEXCOORD_ATTRIBUTE ";\n"
				"uniform mat4 u_projTrans;\n"
				"varying vec4 v_color;\n"
				"varying vec2 v_texCoords;\n"
				"\n"
				"void main()\n"
				"{\n"
				"    v_color = " COLOR_ATTRIBUTE ";\n"
				"    v_texCoords = " TEXCOORD_ATTRIBUTE ";\n"
				//"    gl_Position = u_projTrans * " POSITION_ATTRIBUTE ";\n"
				"}\n";

			const char* fragmentShader =
				"#ifdef GL_ES\n"
				"#define LOWP lowp\n"
				"precision mediump float;\n"
				"#else\n"
				"#endif\n"
				"varying LOWP vec4 v_color;\n"
				"varying vec2 v_texCoords;\n"
				"uniform sampler2D u_texture;\n"
				"void main()\n"
				"{\n"
				"    gl_FragColor = v_color * texture2D(u_texture, v_texCoords);\n"
				"}";


			m_defaultShader = new Shader(vertexShader, fragmentShader);			
		}
		if (m_defaultShader->IsCompiled() == false) {
			return NULL;
		}
		else {
			return m_defaultShader;
		}
	}

	void RenderContext::SwitchTexture(Texture& texture) {
		if (m_lastTextureId != texture.glHandle) {
			texture.Bind();
		}
	}
}