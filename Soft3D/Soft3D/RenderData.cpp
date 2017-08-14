#include "RenderData.h"

namespace Soft3D {

	RenderData* RenderData::CreateRenderData(UInt vertices, UInt vertexSize, UInt indices) {
		if (vertices == 0 || vertexSize == 0) {
			return NULL;
		}

		RenderData* pRenderData = new RenderData();
		pRenderData->vertices = vertices;
		pRenderData->vertexSize = vertexSize;
		pRenderData->verticesData = new Float[vertices * vertexSize];

		if (indices != 0) {
			pRenderData->indicesData = NULL;
			pRenderData->indices = 0;
		}
		else {
			pRenderData->indicesData = new UInt(indices);
			pRenderData->indices = indices;
		}

		return pRenderData;
	}

	void RenderData::DestroyData(){
		if (verticesData != NULL) {
			delete this->verticesData;
			this->verticesData = NULL;
		}

		if (indicesData != NULL) {
			delete this->indicesData;
			this->indicesData = NULL;
		}
	}

}