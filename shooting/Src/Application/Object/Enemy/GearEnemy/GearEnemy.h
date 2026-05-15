#pragma once
#include"../../BaseObject.h"


class C_Explosion;
class C_Score;
class C_Player;

class C_GearEnemy:public C_BaseObject
{
public:

	C_GearEnemy() { Init(); }
	~C_GearEnemy()override { Release(); }

	void Draw()override;
	void Update()override;


	// 敵出現用関数
	void Spawn();

	void SetInstance(std::shared_ptr<C_Score>a_score,
	                 std::shared_ptr<C_Player>a_player) 
					{
		              m_score = a_score; 
					  m_player = a_player;
	                }



	bool          GetAliveFalseFlg()              { return m_aliveFalseFlg; }
	Math::Vector2 GetPos(int a_i)                 { return s_gearEnemy[a_i].m_pos; }
	float         GetRadius()                     { return m_radius; }
	float         GetAttackPow()                  { return m_attackPow; }
	int           GetNum()                        { return gearEnemyNum; }
	bool          GetAliveFlg(int a_i)            { return s_gearEnemy[a_i].m_aliveFlg; }
	void          Damage(int a_i, float a_damage) { m_hp[a_i]-=a_damage; }
	Element       GetElement(int a_i)             { return s_gearEnemy[a_i].m_nowElement; }

	void          SetMatchupType(int a_i, MatchupType a_matchupType) { e_matchupType[a_i] = a_matchupType; }
	float         GetScore(MatchupType a_matchupType);

private:

	void Init()override;
	void Release()override;
	void Move();
	void Animation();
	void AliveState();

	
	static const int gearEnemyNum = 20;

	KdTexture   m_gearEnemyTex;
	S_Object    s_gearEnemy[gearEnemyNum]{};
	float       m_animCnt[gearEnemyNum]{};
	float       m_hp[gearEnemyNum] = {};
	const float m_maxHp = 60;
	const float m_attackPow = 6;
	const float m_movePowX = -1.5f;
	MatchupType   e_matchupType[gearEnemyNum] = {};

	float       m_aliveFalseCnt = {};
	bool        m_aliveFalseFlg = {};
	int         m_randomElement = {};
	const float gearEnemyScore = 10000;

	bool        m_spawnFlg = {};

	std::shared_ptr<C_Explosion>m_explosion[gearEnemyNum];

	std::shared_ptr<C_Score>m_score;

	std::shared_ptr<C_Player>m_player;
	
	
};