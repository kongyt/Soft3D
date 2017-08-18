#ifndef _Mesh_H__
#define _Mesh_H__

#include "DllApi.h"
#include "Types.h"
#include "Shader.h"

namespace Soft3D {

	
	struct VertexAttr {
		int offset;
		int numComponents;
		String alias;
	};

	class DLLAPI Mesh {
	public:
		Mesh(int vertices, int vertexSize, int indices);

	};
}


#endif