#ifndef _GameObject_H__
#define _GameObject_H__

#include <vector>

#include "DllApi.h"
#include "Types.h"
#include "Vector3.h"
#include "ComponentInterface.h"
#include "Matrix4.h"
#include "RenderContext.h"
#include "RenderObject.h"

namespace Soft3D {

	class RenderObject;

	class DLLAPI GameObject{
	public:
		void AddChild(GameObject* child);
		void DelChild(GameObject* child);
		UInt GetChildrenNum();

		virtual void Update(Float delta);
		virtual void Render(RenderContext& renderContext);

		void AddRenderObject(RenderObject* renderObject);
		void DelRenderObject(RenderObject* renderObject);
		UInt GetRenderObjectNum();

		void AddComponent(ComponentInterface* component);
		void DelComponent(ComponentInterface* component);
		UInt GetComponentNum();

		virtual void SetPosition(Float x, Float y, Float z);
		virtual void SetRotation(Float rx, Float ry, Float rz);
		virtual void SetScale(Float sx, Float sy, Float sz);
		Vector3& GetPosition();
		Vector3& GetRotation();
		Vector3& GetScale();

	protected:
		Vector3 position = Vector3(0,0,0);
		Vector3 rotation = Vector3(0,0,0);
		Vector3 scale = Vector3(1,1,1);
		Bool isTransformed = false;
		Matrix4 transformMatrix;		// 相对父节点的本地变换矩阵

	protected:
		GameObject* parent;
		std::vector<GameObject*> children;
		std::vector<RenderObject*> renderObjects;
		std::vector<ComponentInterface*> components;
	};

}

#endif