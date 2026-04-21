#pragma once

#include "State.h"
#include "PlayStage.h"

class C_GameScene :public C_State
{

public:
	C_GameScene() {}
	~C_GameScene() {}

	void Draw()override { playStage.Draw(); }
	void Update()override { playStage.Update(); }
	void Init()override { playStage.Init(); }
private:

	C_PlayStage playStage;
};
