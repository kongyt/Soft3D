#ifndef _Render_Data_H__
#define _Render_Data_H__

#include "DllApi.h"
#include "Types.h"

namespace Soft3D {

	class DLLAPI RenderData {
	public:
		static RenderData* CreateRenderData(UInt vertices, UInt vertexSize, UInt indices);
		void DestroyData();
		
	public:
		Bool cached;
		UInt verticesCachedId;
		UInt indicesCachedId;

		Float* verticesData;
		UInt vertices;
		UInt vertexSize;

		UInt * indicesData;
		UInt indices;
	};

}

#endif