#include "RenderContext.h"
#include "Shader.h"
#include <assert.h>

namespace Soft3D {
	
	void BuildAttribList(EGLint *attribList)
	{
		int    nAttribCount = 0;

		attribList[nAttribCount++] = EGL_RED_SIZE;
		attribList[nAttribCount++] = 5;
		attribList[nAttribCount++] = EGL_GREEN_SIZE;
		attribList[nAttribCount++] = 6;
		attribList[nAttribCount++] = EGL_BLUE_SIZE;
		attribList[nAttribCount++] = 5;
		attribList[nAttribCount++] = EGL_ALPHA_SIZE;
		attribList[nAttribCount++] = 0;
		attribList[nAttribCount++] = EGL_DEPTH_SIZE;
		attribList[nAttribCount++] = 16;
		attribList[nAttribCount++] = EGL_STENCIL_SIZE;
		attribList[nAttribCount++] = 0;
		attribList[nAttribCount++] = EGL_SAMPLES;
		attribList[nAttribCount++] = 4;
		attribList[nAttribCount++] = EGL_NONE;

		assert(nAttribCount < MAX_EGL_ATTRIBUTES);
	}

	Bool RenderContext::Init(HWND hwnd) {
		EGLint attribList[MAX_EGL_ATTRIBUTES];
		EGLint numConfigs;
		EGLint majorVersion;
		EGLint minorVersion;

		/// Build up the attribute list
		BuildAttribList(attribList);

		// Get Display
		m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		if (m_eglDisplay == EGL_NO_DISPLAY)
		{
			assert(0 && "eglGetDisplay failed");
			return FALSE;
		}

		// Initialize EGL
		if (!eglInitialize(m_eglDisplay, &majorVersion, &minorVersion))
		{
			assert(0 && "eglInitialize failed");
			return FALSE;
		}

		// Get configs
		if (!eglGetConfigs(m_eglDisplay, NULL, 0, &numConfigs))
		{
			assert(0 && "eglGetConfigs failed");
			return FALSE;
		}

		// Choose config
		if (!eglChooseConfig(m_eglDisplay, attribList, &m_eglConfig, 1, &numConfigs))
		{
			assert(0 && "eglChooseConfig failed");
			return FALSE;
		}

		// Create a surface
		m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig, NativeWindowType(hwnd), NULL);
		if (m_eglSurface == EGL_NO_SURFACE)
		{
			assert(0 && "eglCreateWindowSurface failed");
			return FALSE;
		}

		// Create a GL context
		EGLint ctxAttribList[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
		m_eglContext = eglCreateContext(m_eglDisplay, m_eglConfig, EGL_NO_CONTEXT, ctxAttribList);
		if (m_eglContext == EGL_NO_CONTEXT)
		{
			assert(0 && "eglCreateContext failed");
			return FALSE;
		}

		// Make the context current
		if (!eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext))
		{
			assert(0 && "eglMakeCurrent failed");
			return FALSE;
		}
		return TRUE;
	}
	
	void RenderContext::Destroy() {
		eglDestroyContext(m_eglDisplay, m_eglContext);
		eglDestroySurface(m_eglDisplay, m_eglSurface);
		eglTerminate(m_eglDisplay);
	}

	void RenderContext::SwapBuffer() {
		eglSwapBuffers(m_eglDisplay, m_eglSurface);
	}

	void RenderContext::SetCameraMatrix(Matrix4& cameraMatrix) {
		m_projectionMatrix.Set(cameraMatrix);
		m_combinedMatrix.Set(m_projectionMatrix).Mul(m_transformMatrix);
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
				"    gl_Position = u_projTrans * " POSITION_ATTRIBUTE ";\n"
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

	void RenderContext::Begin() {
		glBindTexture(GL_TEXTURE_2D, 0);
		m_lastTextureId = 0;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RenderContext::End() {		
		SwapBuffer();
	}

	void RenderContext::SwitchTexture(Texture& texture) {
		if (m_lastTextureId != texture.glHandle) {
			texture.Bind();
		}		
	}

}