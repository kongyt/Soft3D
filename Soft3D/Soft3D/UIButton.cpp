#include "UIButton.h"

namespace Soft3D{

	UIButton::UIButton(TextureRegion* upTexRegion, TextureRegion* downTexRegion) {
		this->upTexRegion = upTexRegion;
		this->downTexRegion = downTexRegion;
		this->upTexRegion = upTexRegion;
		this->isPressed = false;
		this->SetClickListener(this);
	}

	UIButton::UIButton(TextureRegion* upTexRegion) {
		this->upTexRegion = upTexRegion;
		this->downTexRegion = upTexRegion;
		this->usedTexRegion = upTexRegion;
		this->isPressed = false;
		this->SetClickListener(this);
	}

	Bool UIButton::TouchDown(Float x, Float y, Int keyCode) {
		this->isPressed = true;
		this->usedTexRegion = downTexRegion;
		this->SetColor(0.75f, 0.75f, 0.75f, 1);
		return true;
	}

	Bool UIButton::TouchDragged(Float x, Float y, Int keyCode) {
		return true;
	}

	Bool UIButton::TouchUp(Float x, Float y, Int keyCode) {
		this->isPressed = false;
		this->usedTexRegion = upTexRegion;
		this->SetColor(1, 1, 1, 1);
		return true;
	}

	void UIButton::Clicked() {

	}

	void UIButton::SetPosition(Float x, Float y) {
		this->x = x;
		this->y = y;
	}


	void UIButton::SetRotation(Float rotation) {
		this->rotation = rotation;
	}

	void UIButton::SetSize(Float width, Float height) {
		this->width = width;
		this->height = height;
	}

	void UIButton::SetOrigin(Float originX, Float originY) {
		this->originX = originX;
		this->originY = originY;
	}

	void UIButton::SetColor(Color color) {
		this->color = color;
	}

	void UIButton::SetColor(Float r, Float g, Float b, Float a) {
		this->color.r = r;
		this->color.g = g;
		this->color.b = b;
		this->color.a = a;
	}

	void UIButton::UpdateVertexs(Float parentAlpha) {

		float p1x = x + (-originX)*scaleX;
		float p1y = y + (-originY)*scaleY;
		float p2x = p1x;
		float p2y = y + (height - originY)*scaleY;
		float p3x = x + (width - originX)*scaleX;
		float p3y = p1y;
		float p4x = p3x;
		float p4y = p2y;

		float radius = rotation / 180.0f*MathUtils::Pi();
		float cosTheta = cos(radius);
		float sinTheta = sin(radius);

		vertices[P1X] = (p1x*cosTheta - p1y*sinTheta);
		vertices[P1Y] = (p1y*cosTheta + p1x*sinTheta);
		vertices[P1R] = color.r;
		vertices[P1G] = color.g;
		vertices[P1B] = color.b;
		vertices[P1A] = color.a * parentAlpha;
		vertices[P1U] = usedTexRegion->u1;
		vertices[P1V] = usedTexRegion->v2;

		vertices[P2X] = (p2x*cosTheta - p2y*sinTheta);
		vertices[P2Y] = (p2y*cosTheta + p2x*sinTheta);
		vertices[P2R] = color.r;
		vertices[P2G] = color.g;
		vertices[P2B] = color.b;
		vertices[P2A] = color.a * parentAlpha;
		vertices[P2U] = usedTexRegion->u1;
		vertices[P2V] = usedTexRegion->v1;

		vertices[P3X] = (p3x*cosTheta - p3y*sinTheta);
		vertices[P3Y] = (p3y*cosTheta + p3x*sinTheta);
		vertices[P3R] = color.r;
		vertices[P3G] = color.g;
		vertices[P3B] = color.b;
		vertices[P3A] = color.a * parentAlpha;
		vertices[P3U] = usedTexRegion->u2;
		vertices[P3V] = usedTexRegion->v2;

		vertices[P4X] = (p4x*cosTheta - p4y*sinTheta);
		vertices[P4Y] = (p4y*cosTheta + p4x*sinTheta);
		vertices[P4R] = color.r;
		vertices[P4G] = color.g;
		vertices[P4B] = color.b;
		vertices[P4A] = color.a * parentAlpha;
		vertices[P4U] = usedTexRegion->u2;
		vertices[P4V] = usedTexRegion->v1;

	}

	void UIButton::Render(RenderContext& renderContext, Float parentAlpha) {
		if (this->visiable) {
			UpdateVertexs(parentAlpha);

			Shader* shader = renderContext.GetDefaultShader();
			if (shader != NULL) {

				shader->Begin();

				shader->SetUniformMatrix("u_projTrans", renderContext.GetCombinedMatrix());
				shader->SetUniformi("u_texture", 0);

				renderContext.SwitchTexture(*(usedTexRegion->texture));

				int positionLoc = shader->GetAttrLocation(POSITION_ATTRIBUTE);
				glEnableVertexAttribArray(positionLoc);
				glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, BUTTON_SIZE, &vertices[POSITION_OFFSET]);

				int colorLoc = shader->GetAttrLocation(COLOR_ATTRIBUTE);
				glEnableVertexAttribArray(colorLoc);
				glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_TRUE, BUTTON_SIZE, &vertices[COLOR_OFFSET]);

				int texCoordLoc = shader->GetAttrLocation(TEXCOORD_ATTRIBUTE);
				glEnableVertexAttribArray(texCoordLoc);
				glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, BUTTON_SIZE, &vertices[TEXCOORD_OFFSET]);

				glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, indices);

				shader->End();


			}
		}
	}


}