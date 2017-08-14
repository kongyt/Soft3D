#ifndef _GameObject_H__
#define _GameObject_H__

#include <vector>

#include "DllApi.h"
#include "Types.h"
#include "Vector3.h"
#include "ComponentInterface.h"
#include "Matrix4.h"

namespace Soft3D {

	class RenderSystemInterface;
	class RenderObject;

	class DLLAPI GameObject{
	public:
		void AddChild(GameObject* child);
		void DelChild(GameObject* child);
		UInt GetChildrenNum();

		void Update(Float delta);
		void Render(RenderSystemInterface* renderSystemInterface);

		void AddRenderObject(RenderObject* renderObject);
		void DelRenderObject(RenderObject* renderObject);
		UInt GetRenderObjectNum();

		void AddComponent(ComponentInterface* component);
		void DelComponent(ComponentInterface* component);
		UInt GetComponentNum();

	public:
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;
		Matrix4 transformMatrix;		// 相对父节点的本地变换矩阵

	private:
		
		GameObject* parent;
		std::vector<GameObject*> children;
		std::vector<RenderObject*> renderObjects;
		std::vector<ComponentInterface*> components;
	};

}

#endif