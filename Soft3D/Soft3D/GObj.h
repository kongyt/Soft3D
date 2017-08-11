#ifndef _GObj_H__
#define _GObj_H__

#include <vector>

#include "DllApi.h"
#include "Types.h"
#include "Vector3.h"
#include "ComponentInterface.h"

namespace Soft3D {

	class DLLAPI GObj{
	public:
		void AddChild(GObj* child);
		void DelChild(GObj* child);
		UInt GetChildrenNum();

		void AddComponent(ComponentInterface* component);
		void DelComponent(ComponentInterface* component);
		UInt GetComponentNum();

	public:
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;


	private:
		std::vector<GObj*> children;
		std::vector<ComponentInterface*> components;
	};

}

#endif