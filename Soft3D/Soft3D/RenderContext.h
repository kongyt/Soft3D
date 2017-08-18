#ifndef _Render_Context_H__
#define _Render_Context_H__

#include <Windows.h>
#include <stack>

#include "GLES_Support.h"

#include "DllApi.h"
#include "Matrix4.h"
#include "Shader.h"
#include "Texture.h"

#define MAX_EGL_ATTRIBUTES 20

namespace Soft3D {

	class DLLAPI RenderContext {
	public:
		Bool Init(HWND hwnd);
		void Destroy();
		void SwapBuffer();
		void SetCameraMatrix(Matrix4& cameraMatrix);

		void PushTransformMatrix(Matrix4& transformMatrix);
		void PopTransformMatrix();
		Matrix4& GetCombinedMatrix();
		Shader* GetDefaultShader();
		void SwitchTexture(Texture& texture);

	private:		
		EGLDisplay m_eglDisplay;
		EGLConfig m_eglConfig;
		EGLSurface m_eglSurface;
		EGLContext m_eglContext;
		std::stack<Matrix4*> m_transMatrixStack;

		Matrix4 m_transformMatrix;
		Matrix4 m_projectionMatrix;
		Matrix4 m_combinedMatrix;

		Shader* m_defaultShader;

		int m_lastTextureId;
	};

}


#endif