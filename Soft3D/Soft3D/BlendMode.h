#ifndef _Blend_Mode_H__
#define _Blend_Mode_H__

#include "DllApi.h"

#define Blend_Zero					0
#define Blend_One					1
#define Blend_Src_Color				2
#define Blend_One_Minus_Src_Color	3


namespace Soft3D {

	enum DLLAPI Blend {
		Zero				= 0,
		One					= 1,
		Src_Color			= 2,
		One_Minus_Src_Color	= 3,
		Dst_Color			= 4,
		One_Minus_Dst_Color	= 5,
		Src_Alpha			= 6,
		One_Minus_Src_Alpha	= 7,
		Dst_Alpha			= 8,
		One_Minus_Dst_Alpha	= 9,
		Src_Alpha_Saturate	= 10

	};

	class DLLAPI BlendMode {
	public:
		Blend srcBlend;
		Blend dstBlend;
	};

}


#endif
