#ifndef _GLSL_Shader_H__
#define _GLSL_Shader_H__

#include <map>

#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glew.h>

#include "../Soft3D/DllApi.h"
#include "../Soft3D/Types.h"
#include "../Soft3D/Shader.h"

namespace Soft3D {

	class GLShaderManager {
	public:
		UInt GetDefaultShader();
		UInt AddShader(Shader& shader);
		void DelShader(UInt shaderId);
		void EnableShader(UInt shaderId);
		void DisableShader(UInt shaderId);


	private:
		Bool m_defaultShaderReady;
		UInt m_defaultShader;
		UInt m_currentShader;

	};

}


#endif
