#ifndef _Demo_Game_H__
#define _Demo_Game_H__

#include "../Soft3D/Soft3D.h"
#include "TestScene.h"

class DemoGame : public Soft3D::Game {
public:
	void Start() {
		this->SetScene(new TestScene());
	}

};

#endif