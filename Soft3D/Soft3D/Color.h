#ifndef _Color_H__
#define _Color_H__

#include "DllApi.h"
#include "Types.h"
#include "MathUtils.h"

namespace Soft3D{

	class DLLAPI Color{
	public:
		Color();
		Color(Float r, Float g, Float b, Float a);
		Color(UInt color);
		Color* Clone();

		UInt ToUint();
		void ToFloatBits(Float* pfloat);
	public:
		Float	r;
		Float	g;
		Float	b;
		Float	a;

	public:
		const static Color Black;           // 黑色
		const static Color Red;             // 红色
		const static Color Green;           // 绿色
		const static Color Yellow;          // 黄色
		const static Color Blue;            // 蓝色
		const static Color Magenta;         // 洋红
		const static Color Cyan;            // 青色
		const static Color DarkGray;        // 深灰
		const static Color LightGray;       // 浅灰
		const static Color Brown;           // 褐色
		const static Color PumpkinOrange;   // 南瓜橙
		const static Color PastelPink;      // 粉红
		const static Color BarneyPurple;    // 巴尼紫
		const static Color White;           // 白色
	};




}

#endif