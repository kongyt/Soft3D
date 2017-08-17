#ifndef _Mesh_H__
#define _Mesh_H__

#include "DllApi.h"
#include "Types.h"

namespace Soft3D {

	
	struct VertexAttr {
		int offset;
		int numComponents;
		String alias;

	};

	class DLLAPI Mesh {
		Mesh(int vertices, int indices, int vertexSize,) {
			
		}

	};

}


#endif