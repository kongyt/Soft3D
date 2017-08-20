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
		const static Color Black;           // ��ɫ
		const static Color Red;             // ��ɫ
		const static Color Green;           // ��ɫ
		const static Color Yellow;          // ��ɫ
		const static Color Blue;            // ��ɫ
		const static Color Magenta;         // ���
		const static Color Cyan;            // ��ɫ
		const static Color DarkGray;        // ���
		const static Color LightGray;       // ǳ��
		const static Color Brown;           // ��ɫ
		const static Color PumpkinOrange;   // �Ϲϳ�
		const static Color PastelPink;      // �ۺ�
		const static Color BarneyPurple;    // ������
		const static Color White;           // ��ɫ
	};




}

#endif