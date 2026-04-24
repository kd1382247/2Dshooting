#pragma once
#include "../BaseScene/BaseScene.h"

//前方宣言
class C_PlayStage;

class C_GameScene :public C_BaseScene
{

public:
	C_GameScene() { Init(); }
	~C_GameScene() {}

	void Draw()override;
	void Update()override;
	void Init()override;


private:

	std::shared_ptr<C_PlayStage>m_playStage;

};
