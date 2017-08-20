#ifndef _Input_H__
#define _Input_H__

#include <Windows.h>

#include "DllApi.h"
#include "Types.h"




namespace Soft3D {

	class InputProcessor;

	enum KeyCode {
        Mouse_Left = VK_LBUTTON,
        Mouse_Mid = VK_MBUTTON,
        Mouse_Right = VK_RBUTTON,

        Key_Up = VK_UP,
        Key_Down = VK_DOWN,
        Key_Left = VK_LEFT,
        Key_Right = VK_RIGHT,

        Key_0 = 48,
        Key_1 = 49,
        Key_2 = 50,
        Key_3 = 51,
        Key_4 = 52,
        Key_5 = 53,
        Key_6 = 54,
        Key_7 = 55,
        Key_8 = 56,
        Key_9 = 57,

        Key_A = 65,
        Key_B = 66,
        Key_C = 67,
        Key_D = 68,
        Key_E = 69,
        Key_F = 70,
        Key_G = 71,
        Key_H = 72,
        Key_I = 73,
        Key_J = 74,
        Key_K = 75,
        Key_L = 76,
        Key_M = 77,
        Key_N = 78,
        Key_O = 79,
        Key_P = 80,
        Key_Q = 81,
        Key_R = 82,
        Key_S = 83,
        Key_T = 84,
        Key_U = 85,
        Key_V = 86,
        Key_W = 87,
        Key_X = 88,
        Key_Y = 89,
        Key_Z = 90,

        Key_F1 = VK_F1,
        Key_F2 = VK_F2,
        Key_F3 = VK_F3,
        Key_F4 = VK_F4,
        Key_F5 = VK_F5,
        Key_F6 = VK_F6,
        Key_F7 = VK_F7,
        Key_F8 = VK_F8,
        Key_F9 = VK_F9,
        Key_F10 = VK_F10,
        Key_F11 = VK_F11,
        Key_F12 = VK_F12,

        Key_Esc = VK_ESCAPE,
        Key_TAB = VK_TAB,
        Key_Left_Ctrl = VK_LCONTROL,
        Key_Left_Shift = VK_LSHIFT,
        Key_Left_Alt = VK_LMENU,
        Key_Right_Ctrl = VK_RCONTROL,
        Key_Right_Shift = VK_RSHIFT,
        Key_Rgiht_Alt = VK_RMENU,
        Key_Plus = VK_OEM_PLUS,
        Key_Minus = VK_OEM_MINUS,
        Key_Backspace = VK_BACK,
        Key_Enter = VK_RETURN,

        Key_Num0 = VK_NUMPAD0,
        Key_Num1 = VK_NUMPAD1,
        Key_Num2 = VK_NUMPAD2,
        Key_Num3 = VK_NUMPAD3,
        Key_Num4 = VK_NUMPAD4,
        Key_Num5 = VK_NUMPAD5,
        Key_Num6 = VK_NUMPAD6,
        Key_Num7 = VK_NUMPAD7,
        Key_Num8 = VK_NUMPAD8,
        Key_Num9 = VK_NUMPAD9,

        Key_Num_Plus = VK_ADD,
        Key_Num_Minus = VK_SUBTRACT,
        Key_Num_Mul = VK_MULTIPLY,
        Key_Num_Div = VK_DIVIDE,
        Key_Num_Enter = VK_SEPARATOR,
        Key_Num_Dot = VK_DECIMAL,

	};

	class DLLAPI Input {
	public:
		static void SetProcessor(InputProcessor* processor);
		static InputProcessor* GetProcessor();

	private:
		static InputProcessor* inputProcessor;

	};

}



#endif