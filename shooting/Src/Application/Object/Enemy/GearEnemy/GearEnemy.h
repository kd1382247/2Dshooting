#pragma once
#include"../../BaseObject.h"


class C_Explosion;

class C_GearEnemy:public C_BaseObject
{
public:

	C_GearEnemy() { Init(); }
	~C_GearEnemy()override { Release(); }

	void Draw()override;
	void Update()override;
	
	Math::Vector2 GetPos(int a_i) { return s_gearEnemy[a_i].m_pos; }
	float         GetRadius() { return m_radius; }
	int           GetNum() { return gearEnemyNum; }
	bool          GetAliveFlg(int a_i) { return s_gearEnemy[a_i].m_aliveFlg; }

	void Damage(int a_i) { m_hp[a_i]--; }
	void SetHp(int a_hp,int a_i) { m_hp[a_i] = a_hp; }

	Element GetElement(int a_i) { return s_gearEnemy[a_i].m_nowElement; }

	// 敵出現用関数
	void Spawn();

	
private:


	void Init()override;
	void Release()override;
	void Move();
	void Animation();
	void AliveState();


	static const int gearEnemyNum = 18;

	S_Object   s_gearEnemy[gearEnemyNum]{};
	float      m_animCnt[gearEnemyNum]{};
	float      m_hp[gearEnemyNum] = {};

	KdTexture  m_gearEnemyTex;

	std::shared_ptr<C_Explosion>m_explosion[gearEnemyNum];

	
	
};