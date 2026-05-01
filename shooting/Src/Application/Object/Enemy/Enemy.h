#pragma once
#include"../BaseObject.h"

class C_Enemy:public C_BaseObject
{
public:

	C_Enemy() { Init(); }
	~C_Enemy()override { Release(); }

	void Draw()override;
	void Update()override;
	
	Math::Vector2 GetPos(int a_i) { return s_enemy[a_i].m_pos; }
	float         GetRadius() { return m_radius; }
	int           GetNum() { return enemyNum; }
	bool          GetAliveFlg(int a_i) { return s_enemy[a_i].m_aliveFlg; }

	void SetAliveFlg(int a_i, bool a_flg) { s_enemy[a_i].m_aliveFlg = a_flg; }

	
private:

	void Init()override;
	void Release()override;

	static const int enemyNum = 18;

	S_Object   s_enemy[enemyNum]{};
	float      m_animCnt[enemyNum]{};
	
	KdTexture  m_enemyTex;
	
};