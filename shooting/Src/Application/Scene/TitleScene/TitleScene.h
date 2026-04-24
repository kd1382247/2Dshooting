#pragma once

#include "../BaseScene/BaseScene.h"


class C_TitleScene :public C_BaseScene
{
public:


	C_TitleScene() {}
	~C_TitleScene() {}

	void Draw()override;
	void Update()override;
	void Init()override;

private:


};