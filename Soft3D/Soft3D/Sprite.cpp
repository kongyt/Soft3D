#include "Sprite.h"

namespace Soft3D {

	Sprite::Sprite(Texture* texture) {
		this->texture = texture;
	}

	void Sprite::Render(RenderContext& renderContext) {
		if (visiable) {			
			Shader* shader = renderContext.GetDefaultShader();
			if (shader != NULL){
				shader->Begin();
				renderContext.SwitchTexture(*texture);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);				
				shader->End();
			}
		}
	}

}