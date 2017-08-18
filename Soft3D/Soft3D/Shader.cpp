#include "Shader.h"
#include "GLES_Support.h"
#include "Debug.h"

namespace Soft3D {

	Shader::Shader(const char* vertexShaderSrc, const char* fragmentShaderSrc) {
		CompileShader(vertexShaderSrc, fragmentShaderSrc);
	}

	void Shader::Begin() {
		glUseProgram(m_program);
	}

	void Shader::End() {
		glUseProgram(0);
	}


	Bool Shader::IsCompiled() {
		return m_isCompiled;
	}

	void Shader::CompileShader(const char* vertexShader, const char* fragmentShader) {
		m_vertexShaderId = LoadShader(GL_VERTEX_SHADER, vertexShader);
		m_fragmentShaderId = LoadShader(GL_FRAGMENT_SHADER, fragmentShader);

		if (m_vertexShaderId == -1 || m_fragmentShaderId == -1) {
			m_isCompiled = false;
			return;
		}

		m_program = LinkProgram();
		if (m_program == -1) {
			m_isCompiled = false;
			return;
		}
		m_isCompiled = true;
	}

	int Shader::LoadShader(int type, const char* source) {
		int shader = glCreateShader(type);
		if (shader == 0) 
			return -1;

		const char* src[1];
		src[0] = source;
		glShaderSource(shader, 1, src, NULL);
		glCompileShader(shader);

		int testVal;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &testVal);
		if (testVal == 0) {
			char buf[1024] = {0};
			int len;
			glGetShaderInfoLog(shader, sizeof(buf), &len, buf);
			Debug::Error(buf);
			return -1;
		}
		return shader;

	}

	int Shader::LinkProgram() {
		int program = glCreateProgram();
		if (program == 0)
			return -1;

		glAttachShader(program, m_vertexShaderId);
		glAttachShader(program, m_fragmentShaderId);
		glLinkProgram(program);

		int testVal;
		glGetProgramiv(program, GL_LINK_STATUS, &testVal);
		if (testVal == 0) {
			return -1;
		}

		return program;
	}


}