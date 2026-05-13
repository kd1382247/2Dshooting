#pragma once
#include"../../BaseObject.h"

class C_Explosion;
class C_Score;
class C_Player;

enum EnemyMoveType
{
	Rotation,
	Idle
};

struct S_Center
{
	Math::Vector2 m_pos = {};
	Math::Vector2 m_move = {};
	Math::Matrix  m_mat;
	bool          m_aliveFlg = {};
};

class C_SpikeEnemy:public C_BaseObject
{
public:

	C_SpikeEnemy() { Init(); }
	~C_SpikeEnemy()override { Release(); }


	void Draw()override;
	void Update()override;
	void Spawn();

	bool GetAliveFalseFlg() { return m_aliveFalseFlg; }

	void SetInstance(std::shared_ptr<C_Score>a_score,
					 std::shared_ptr<C_Player>a_player)
					{
						m_score = a_score; 
						m_player = a_player;
					}

	// 当たり判定クラスで呼び出す関数
	Math::Vector2 GetPos(int a_i)                 { return s_spikeEnemy[a_i].m_pos; }
	float         GetRadius()                     { return m_radius; }
	float         GetAttackPow()                  { return m_attackPow; }
	int           GetNum()                        { return spikeEnemyNum; }
	bool          GetAliveFlg(int a_i)            { return s_spikeEnemy[a_i].m_aliveFlg; }
	void          Damage(int a_i, float a_damage) { m_hp[a_i]-=a_damage; }
	Element       GetElement(int a_i)             { return s_spikeEnemy[a_i].m_nowElement; }

	void          SetMatchupType(int a_i, MatchupType a_matchupType) { e_matchupType[a_i] = a_matchupType; }
	float         GetScore(MatchupType a_matchupType);

private:

	void Init()override;
	void Release()override;

	void Move();
	void Animation();
	void AliveState();


	KdTexture        m_spikeEnemyTex;
	static const int spikeEnemyNum = 20;
	S_Object         s_spikeEnemy[spikeEnemyNum] = {};
	float            m_animCnt[spikeEnemyNum] = {};
	float            m_hp[spikeEnemyNum] = {};
	const float      m_maxHp = 40;
	const float      m_attackPow=8;
	MatchupType      e_matchupType[spikeEnemyNum] = {};

	float            m_aliveFalseCnt = {};
	bool             m_aliveFalseFlg = {};

	static const int centerNum = 4;
	S_Center         s_center[centerNum] = {};
	const float      m_movePowX = -1.5f;

	float            m_degTable[5] = {0,90,180,270,0};
	float            m_deg[spikeEnemyNum] = {};

	EnemyMoveType    m_moveTypeTable[5] = { Rotation,Rotation, Rotation, Rotation,Idle };
	EnemyMoveType    m_enemyMoveType[spikeEnemyNum];

	int              m_number = {};

	int              m_randomElement = {};

	const float      spikeEnemyScore = 15000;


	std::shared_ptr<C_Explosion>m_explosion[spikeEnemyNum];

	std::shared_ptr<C_Score>m_score;

	std::shared_ptr<C_Player>m_player;
};
