#include "GLShaderManager.h"
#include "RenderSystem_GL.h"

namespace Soft3D {

	static const char *defaultVP =
		"attribute vec4 vVertex;"
		"void main(void) "
		"{ gl_Position = vVertex; "
		"}";

	static const char* defaultFP = 
		"uniform vec4 vColor;"
		"void main(void) "
		"{ gl_FragColor = vColor;"
		"}";

	UInt GLShaderManager::GetDefaultShader() {
		GLuint hVertexShader;
		GLuint hFragmentShader;
		GLuint hReturn = 0;
		GLint testVal;

		hVertexShader = glCreateShader(GL_VERTEX_SHADER);
		hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(hVertexShader, 1, &defaultVP, NULL);
		glShaderSource(hFragmentShader, 1, &defaultFP, NULL);

		glCompileShader(hVertexShader);
		glCompileShader(hFragmentShader);

		glGetShaderiv(hVertexShader, GL_COMPILE_STATUS, &testVal);
		if (testVal == GL_FALSE) {
			glDeleteShader(hVertexShader);
			glDeleteShader(hFragmentShader);
			return 0;
		}

		glGetShaderiv(hFragmentShader, GL_COMPILE_STATUS, &testVal);
		if (testVal == GL_FALSE) {
			glDeleteShader(hVertexShader);
			glDeleteShader(hFragmentShader);
			return 0;
		}
		// 创建最终的程序对象
		hReturn = glCreateProgram();

		glAttachShader(hReturn, hVertexShader);
		glAttachShader(hReturn, hFragmentShader);

		glBindAttribLocation(hReturn, 0, "vVertex");

		glLinkProgram(hReturn);

		glDeleteShader(hVertexShader);
		glDeleteShader(hFragmentShader);

		glGetShaderiv(hReturn, GL_LINK_STATUS, &testVal);
		if (testVal == GL_FALSE) {
			glDeleteProgram(hReturn);
			return 0;
		}

		return hReturn;
	}

	UInt GLShaderManager::AddShader(Shader& shader) {
		// TODO
		return 0;
	}
	
	void GLShaderManager::DelShader(UInt shaderId) {
		glDeleteProgram(shaderId);
	}

	void GLShaderManager::EnableShader(UInt shaderId) {
		glUseProgram(shaderId);
	}

	void GLShaderManager::DisableShader(UInt shaderId) {
		if (m_defaultShaderReady) {
			glUseProgram(m_defaultShader);
		}
	}

}