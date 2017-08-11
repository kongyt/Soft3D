#ifndef _Component_Interface_H__
#define _Component_Interface_H__

#include "Types.h"

namespace Soft3D {

	class GObj;

	class ComponentInterface {

	public:
		GObj* owner;
		Bool  active;

	};

}


#endif