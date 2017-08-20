#include <Windows.h>

#include "Input.h"
#include "InputProcessor.h"


namespace Soft3D {

	InputProcessor* Input::inputProcessor = NULL;

	void Input::SetProcessor(InputProcessor* processor) {
		Input::inputProcessor = processor;
	}

	InputProcessor* Input::GetProcessor() {
		return Input::inputProcessor;
	}


}

