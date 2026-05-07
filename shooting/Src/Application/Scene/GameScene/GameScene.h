#pragma once
#include<vector>
#include "../BaseScene.h"

//前方宣言
class C_BaseObject;
class C_GameUI;
class C_Collision;
class C_Boss;

class C_GameScene :public C_BaseScene
{

public:
	C_GameScene() { Init(); }
	~C_GameScene() override{}

	void Draw()override;
	void Update()override;


private:

	void Init()override;


	std::shared_ptr<C_GameUI> m_gameUi;

	std::shared_ptr<C_Collision>m_collision;


	std::shared_ptr<C_Boss>m_boss;

	std::vector<std::shared_ptr<C_BaseObject>>m_objList;

};
