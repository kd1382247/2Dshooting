#pragma once

#include "../Base/BaseScene.h"

class C_Title;

class C_TitleScene :public C_BaseScene
{
public:


	C_TitleScene() { Init(); }
	~C_TitleScene() {}

	void Draw()override;
	void Update()override;
	void Init()override;

private:

	std::shared_ptr<C_Title> m_title;

};