#pragma once
#include"../../BaseObject.h"

class C_Explosion;

enum EnemyMoveType
{
	Rotation,
	Idle
};

struct S_Center
{
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Matrix  m_mat;
	bool          m_aliveFlg;
};

class C_SpikeEnemy:public C_BaseObject
{
public:

	C_SpikeEnemy() { Init(); }
	~C_SpikeEnemy()override { Release(); }


	void Draw()override;
	void Update()override;
	void Spawn();


	// 当たり判定クラスで呼び出す関数
	Math::Vector2 GetPos(int a_i) { return s_spikeEnemy[a_i].m_pos; }
	float         GetRadius() { return m_radius; }
	int           GetNum() { return spikeEnemyNum; }
	bool          GetAliveFlg(int a_i) { return s_spikeEnemy[a_i].m_aliveFlg; }
	void Damage(int a_i) { m_hp[a_i]--; }
	void SetHp(int a_hp, int a_i) { m_hp[a_i] = a_hp; }


	Element GetElement(int a_i) { return s_spikeEnemy[a_i].m_nowElement; }

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


	static const int centerNum = 4;
	S_Center         s_center[centerNum] = {};
	Math::Vector2    m_posTable[centerNum] = { {800,-100},{1300,200},{1800,-100},{2300,200} };

	float            m_degTable[5] = {0,90,180,270,0};
	float            m_deg[spikeEnemyNum] = {};

	EnemyMoveType    m_moveTypeTable[5] = { Rotation,Rotation, Rotation, Rotation,Idle };
	EnemyMoveType    m_enemyMoveType[spikeEnemyNum];

	int           m_number = {};


	std::shared_ptr<C_Explosion>m_explosion[spikeEnemyNum];
};
