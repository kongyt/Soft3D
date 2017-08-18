#ifndef _Shader_H__
#define _Shader_H__

#include "DllApi.h"
#include "Types.h"

#define POSITION_ATTRIBUTE  "a_position"
#define NORMAL_ATTRIBUTE  "a_normal"
#define COLOR_ATTRIBUTE  "a_color"
#define TEXCOORD_ATTRIBUTE  "a_texCoord"
#define TANGENT_ATTRIBUTE  "a_tangent"
#define BINORMAL_ATTRIBUTE  "a_binormal"


namespace Soft3D {

	class DLLAPI Shader {
	public:
		Shader(const char* vertexShaderSrc, const char* fragmentShaderSrc);
		Bool IsCompiled();
		void Begin();
		void End();


	private:
		void CompileShader(const char* vertexShader, const char* fragmentShader);
		int LoadShader(int type, const char* source);
		int LinkProgram();

	public:
		int m_program;
		int m_vertexShaderId;
		int m_fragmentShaderId;
		Bool m_isCompiled;
	};

}

#endif