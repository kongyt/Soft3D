#ifndef _Test_Click_Listener_H__
#define _Test_Click_Listener_H__

#include "../Soft3D/Soft3D.h"

using namespace Soft3D;

class TestClickListener :public ClickListener{
public:
	virtual Bool TouchDown(Float x, Float y, Int keyCode) {
		printf("按下(%f, %f)\n", x, y);
		return true;
	}
	virtual Bool TouchDragged(Float x, Float y, Int keyCode) {
		printf("拖动(%f, %f)\n", x, y);
		return true;
	}
	virtual Bool TouchUp(Float x, Float y, Int keyCode) {
		printf("抬起(%f, %f)\n", x, y);
		return true;
	}
	virtual void Clicked() {
		printf("点击");
	}

};

#endif