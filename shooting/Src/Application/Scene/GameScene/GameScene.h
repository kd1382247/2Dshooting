#pragma once
#include<vector>
#include "../BaseScene.h"

//前方宣言
class C_BaseObject;
class C_BaseEffect;
class C_GameUI;
class C_Collision;
class C_HitEffect;
class C_Explosion;

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
	std::shared_ptr<C_Collision> m_collision;

	std::shared_ptr<C_HitEffect> m_hitEffect;

	std::shared_ptr<C_Explosion>m_explosion;

	std::vector<std::shared_ptr<C_BaseObject>>m_objList;

};
