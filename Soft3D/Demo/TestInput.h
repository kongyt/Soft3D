#ifndef _Test_Input_H__
#define _Test_Input_H__
#include <stdio.h>
#include <stdlib.h>

#include "../Soft3D/Soft3D.h"

using namespace Soft3D;

class TestInput :public InputAdapter {
public:
	Bool KeyDown(Int keyCode) {
		printf("����keyCode=%d ����\n", keyCode);
		switch (keyCode) {
		case KeyCode::Key_Esc:
			Window::Exit();
			break;
		}
		return true;
	}


	Bool KeyUp(Int keyCode) {
		printf("����keyCode=%d ̧��\n", keyCode);
		return true;
	}

	Bool TouchDown(Int screenX, Int screenY, Int keyCode) {
		printf("��갴��x=%d, y = %d, keyCode=%d\n", screenX, screenY, keyCode);
		return true;
	}
	Bool TouchDragged(Int screenX, Int screenY, Int keyCode) {
		printf("����϶�x=%d, y = %d, keyCode=%d \n", screenX, screenY, keyCode);
		return true;
	}
	Bool TouchUp(Int screenX, Int screenY, Int keyCode) {
		printf("���̧��x=%d, y = %d, keyCode=%d \n", screenX, screenY, keyCode);
		return true;
	}

};



#endif