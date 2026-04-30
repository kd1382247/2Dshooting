#pragma once
#include<vector>
#include "../Base/BaseScene.h"

//前方宣言
class C_BaseObject;
class C_GameUI;



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

	std::vector<std::shared_ptr<C_BaseObject>>m_objList;

};
