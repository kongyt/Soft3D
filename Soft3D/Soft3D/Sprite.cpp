#include "Sprite.h"

namespace Soft3D {

	Sprite::Sprite(TextureRegion* textureRegion) {
		this->textureRegion = textureRegion;
		this->SetPosition(0, 0);
		this->SetSize(textureRegion->regionWidth, textureRegion->regionHeight);
		this->SetOrigin(0, 0);
		this->SetRotation(0);
		this->SetColor(1, 1, 1, 1);
	}

	void Sprite::SetPosition(Float x, Float y) {
		this->x = x;
		this->y = y;
		isChanged = true;
	}


	void Sprite::SetRotation(Float rotation) {
		this->rotation = rotation;
		isChanged = true;

	}

	void Sprite::SetSize(Float width, Float height) {
		this->width = width;
		this->height = height;
		isChanged = true;
	}

	void Sprite::SetOrigin(Float originX, Float originY) {
		this->originX = originX;
		this->originY = originY;
		isChanged = true;
	}

	void Sprite::SetColor(Color color) {
		this->color = color;
		isChanged = true;
	}
	
	void Sprite::SetColor(Float r, Float g, Float b, Float a) {
		this->color.r = r;
		this->color.g = g;
		this->color.b = b;
		this->color.a = a;
		isChanged = true;
	}

	void Sprite::updateVertexs() {
		float tmpX = x + originX;
		float tmpY = y + originY;
		float hw = width / 2;
		float hh = height / 2;
		float radius = rotation / 180.0f*MathUtils::Pi();
		float cosTheta = cos(radius);
		float sinTheta = sin(radius);

		vertices[P1X] = tmpX + ((-hw)*cosTheta - (-hh)*sinTheta);
		vertices[P1Y] = tmpY + ((-hh)*cosTheta + (-hw)*sinTheta);
		vertices[P1R] = color.r;
		vertices[P1G] = color.g;
		vertices[P1B] = color.b;
		vertices[P1A] = color.a;
		vertices[P1U] = textureRegion->u1;
		vertices[P1V] = textureRegion->v2;

		vertices[P2X] = tmpX + ((-hw)*cosTheta - (hh)*sinTheta);
		vertices[P2Y] = tmpY + ((hh)*cosTheta + (-hw)*sinTheta);
		vertices[P2R] = color.r;
		vertices[P2G] = color.g;
		vertices[P2B] = color.b;
		vertices[P2A] = color.a;
		vertices[P2U] = textureRegion->u1;
		vertices[P2V] = textureRegion->v1;

		vertices[P3X] = tmpX + ((hw)*cosTheta - (-hh)*sinTheta);
		vertices[P3Y] = tmpY + ((-hh)*cosTheta + (hw)*sinTheta);
		vertices[P3R] = color.r;
		vertices[P3G] = color.g;
		vertices[P3B] = color.b;
		vertices[P3A] = color.a;
		vertices[P3U] = textureRegion->u2;
		vertices[P3V] = textureRegion->v2;

		vertices[P4X] = tmpX + ((hw)*cosTheta - (hh)*sinTheta);
		vertices[P4Y] = tmpY + ((hh)*cosTheta + (hw)*sinTheta);
		vertices[P4R] = color.r;
		vertices[P4G] = color.g;
		vertices[P4B] = color.b;
		vertices[P4A] = color.a;
		vertices[P4U] = textureRegion->u2;
		vertices[P4V] = textureRegion->v1;

	}

	void Sprite::Render(RenderContext& renderContext) {
		if (visiable) {

			if (isChanged == true) {
				isChanged = false;
				updateVertexs();
			}

			Shader* shader = renderContext.GetDefaultShader();
			if (shader != NULL){			
				
				shader->Begin();				

				shader->SetUniformMatrix("u_projTrans", renderContext.GetCombinedMatrix());
				shader->SetUniformi("u_texture", 0);

				renderContext.SwitchTexture(*(textureRegion->texture));
				
				int positionLoc = shader->GetAttrLocation(POSITION_ATTRIBUTE);
				glEnableVertexAttribArray(positionLoc);
				glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, SPRITE_SIZE, &vertices[POSITION_OFFSET]);

				int colorLoc = shader->GetAttrLocation(COLOR_ATTRIBUTE);
				glEnableVertexAttribArray(colorLoc);
				glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_TRUE, SPRITE_SIZE, &vertices[COLOR_OFFSET]);

				int texCoordLoc = shader->GetAttrLocation(TEXCOORD_ATTRIBUTE);
				glEnableVertexAttribArray(texCoordLoc);
				glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, SPRITE_SIZE, &vertices[TEXCOORD_OFFSET]);

				glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, indices);
						
				shader->End();

		
			}
		}
	}

}