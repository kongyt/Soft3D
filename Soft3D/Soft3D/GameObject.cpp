#include "GameObject.h"
#include "Matrix4.h"
#include "RenderContext.h"
#include "Quaternion.h"

namespace Soft3D {

	void GameObject::AddChild(GameObject* child) {
		if (child != NULL) {
			this->children.push_back(child);
			child->parent = this;
		}
	}


	void GameObject::DelChild(GameObject* child) {
		for (auto iter = children.begin(); iter != children.end(); ++iter) {
			if (*iter == child) {
				children.erase(iter);
				break;
			}
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

		// 如果坐标方向缩放发生过改变，则重新计算变换矩阵
		if (isTransformed) {
			transformMatrix.SetToTranslation(position).Rotate(rotation).Scale(scale);
		}

		// 本地变换矩阵压栈	
		renderContext.PushTransformMatrix(transformMatrix);	

		// 渲染所有挂载的可渲染组件
		for (auto iter = renderObjects.begin(); iter != renderObjects.end(); ++iter) {
			(*iter)->Render(renderContext);
		}

		// 渲染所有子物体
		for (auto iter = children.begin(); iter != children.end(); ++iter) {
			(*iter)->Render(renderContext);
		}

		// 本地变换矩阵出栈
		renderContext.PopTransformMatrix();		
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


	void GameObject::SetPosition(Float x, Float y, Float z) {
		position.x = x;
		position.y = y;
		position.z = z;
		isTransformed = true;
	}

	void GameObject::SetRotation(Float rx, Float ry, Float rz){
		rotation.x = rx;
		rotation.y = ry;
		rotation.z = rz;
		isTransformed = true;
	}

	void GameObject::SetScale(Float sx, Float sy, Float sz){
		scale.x = sx;
		scale.y = sy;
		scale.z = sz;
		isTransformed = true;
	}

	Vector3& GameObject::GetPosition() {
		return position;
	}

	Vector3& GameObject::GetRotation() {
		return rotation;
	}

	Vector3& GameObject::GetScale() {
		return scale;
	}

}