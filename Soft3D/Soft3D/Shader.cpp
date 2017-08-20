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

	void Shader::SetUniformMatrix(const char* matName, Matrix4& mat4) {
		auto itor = m_uniforms.find(matName);
		int location;
		if (itor == m_uniforms.end()) {
			location = glGetUniformLocation(m_program, matName);
			m_uniforms.insert(pair<String, Int>(matName, location));
		}
		else {
			location = itor->second;
		}

		glUniformMatrix4fv(location, 1, false, mat4.data);
		
	}

	void Shader::SetUniformi(const char* name, int value){
		auto itor = m_uniforms.find(name);
		int location;
		if (itor == m_uniforms.end()) {
			location = glGetUniformLocation(m_program, name);
			m_uniforms.insert(pair<String, Int>(name, location));
		}
		else {
			location = itor->second;
		}
		glUniform1i(location, value);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 480, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}

	int Shader::GetAttrLocation(const char* name) {
		auto itor = m_attrs.find(name);
		int location;
		if (itor == m_attrs.end()) {
			location = glGetAttribLocation(m_program, name);
			m_attrs.insert(pair<String, Int>(name, location));
		}
		else {
			location = itor->second;
		}
		return location;
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