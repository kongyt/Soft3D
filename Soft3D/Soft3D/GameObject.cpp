#include "GameObject.h"
#include "Matrix4.h"
#include "RenderContext.h"

namespace Soft3D {

	void GameObject::AddChild(GameObject* child) {
		if (child != NULL) {
			this->children.push_back(child);
			child->parent = this;
			this->hasChildren = true;
		}
	}


	void GameObject::DelChild(GameObject* child) {
		for (auto iter = children.begin(); iter != children.end(); ++iter) {
			if (*iter == child) {
				children.erase(iter);
				break;
			}
		}

		if (GetChildrenNum() == 0) {
			this->hasChildren = false;
		}
	}

	UInt GameObject::GetChildrenNum() {
		return children.size();
	}


	void GameObject::Update(Float delta) {
		for (auto iter = children.begin(); iter != children.end(); ++iter) {
			(*iter)->Update(delta);
		}
	}

	void GameObject::Render(RenderContext& renderContext) {	

		// 渲染所有挂载的可渲染组件
		for (auto iter = renderObjects.begin(); iter != renderObjects.end(); ++iter) {
			(*iter)->Render(renderContext);
		}

		// 渲染所有子物体
		if (hasChildren) {
			renderContext.PushTransformMatrix(transformMatrix);	// 本地变换矩阵压栈		
			for (auto iter = children.begin(); iter != children.end(); ++iter) {
				(*iter)->Render(renderContext);
			}
			renderContext.PopTransformMatrix();		
		}
		
	}

	void GameObject::AddRenderObject(RenderObject* renderObject) {
		renderObjects.push_back(renderObject);
	}

	void GameObject::DelRenderObject(RenderObject* renderObject) {
		for (auto iter = renderObjects.begin(); iter != renderObjects.end(); ++iter) {
			if (*iter == renderObject) {
				renderObjects.erase(iter);
				break;
			}
		}
	}

	UInt GameObject::GetRenderObjectNum() {
		return renderObjects.size();
	}

	void GameObject::AddComponent(ComponentInterface* component) {
		components.push_back(component);
	}

	void GameObject::DelComponent(ComponentInterface* component) {
		for (auto iter = components.begin(); iter != components.end(); ++iter) {
			if (*iter == component) {
				components.erase(iter);
				break;
			}
		}
	}

	UInt GameObject::GetComponentNum() {
		return components.size();
	}

}