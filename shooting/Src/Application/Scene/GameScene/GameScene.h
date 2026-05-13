#pragma once
#include<vector>
#include "../BaseScene.h"

//前方宣言
class C_BaseObject;
class C_GameUI;
class C_Collision;
class C_GameController;
class C_Score;
class C_Result;

class C_GameScene :public C_BaseScene
{

public:
	C_GameScene() { Init(); }
	~C_GameScene() override{}

	void Draw()override;
	void Update()override;

private:

	void Init()override;

	// ゲームUI
	std::shared_ptr<C_GameUI>m_gameUi;

	// 当たり判定	
	std::shared_ptr<C_Collision>m_collision;

	// ゲームコントローラー
	std::shared_ptr<C_GameController>m_gameCtr;

	// スコア
	std::shared_ptr<C_Score>m_score;

	// リザルト
	std::shared_ptr<C_Result>m_result;


	std::vector<std::shared_ptr<C_BaseObject>>m_objList;

};
