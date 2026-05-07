#pragma once
#include"../BaseObject.h"

class C_Player;
class C_Explosion;

class C_Boss :public C_BaseObject
{

public:


	C_Boss() { Init(); }
	~C_Boss()override { Release(); }

	void Draw()override;
	void Update()override;

	void SetInstance(std::shared_ptr<C_Player>a_player) { m_player = a_player; }


	// 当たり判定クラスで呼び出す関数
	Math::Vector2 SEnemyGetPos(int a_i) { return s_spikeEnemy[a_i].m_pos; }
	float         SEnemyGetRadius() { return m_sEnemyRadius; }
	int           SEnemyGetNum() { return spikeEnemyNum; }
	bool          SEnemyGetAliveFlg(int a_i) { return s_spikeEnemy[a_i].m_aliveFlg; }
	void          SEnemyDamage(int a_i) { m_sEnemyHp[a_i]--; }
	void          SEnemySetHp(int a_hp, int a_i) { m_sEnemyHp[a_i] = a_hp; }
	Element       SEnemyGetElement(int a_i) { return s_spikeEnemy[a_i].m_nowElement; }



	// 当たり判定クラスで呼び出す関数
	Math::Vector2 GEnemyGetPos(int a_i) { return s_gearEnemy[a_i].m_pos; }
	float         GEnemyGetRadius() { return m_gEnemyRadius; }
	int           GEnemyGetNum() { return gearEnemyNum; }
	bool          GEnemyGetAliveFlg(int a_i) { return s_gearEnemy[a_i].m_aliveFlg; }
	void          GEnemyDamage(int a_i) { m_gEnemyHp[a_i]--; }
	void          GEnemySetHp(int a_hp, int a_i) { m_gEnemyHp[a_i] = a_hp; }
	Element       GEnemyGetElement(int a_i) { return s_gearEnemy[a_i].m_nowElement; }


	Math::Vector2 BossGetPos() { return s_boss.m_pos; }
	float         BossGetRadius() { return m_bossRadius; }
	bool          BossGetAliveFlg() { return s_boss.m_aliveFlg; }
	void          BossDamage() { m_bossHp--; }


private:

	void Init()override;
	void Release()override;

	void DrawBoss();
	void MoveBoss();
	void InitBoss();
	void Action();
	void SetBossMove();


	void DrawSpikeEnemy();
	void MoveSpikeEnemy();
	void InitSpikeEnemy();
	void AliveStateSpikeEnemy();
	void SpawnSpikeEnemy();



	void DrawGearEnemy();
	void MoveGearEnemy();
	void InitGearEnemy();
	void AliveStateGearEnemy();
	void SpawnGearEnemy();


	KdTexture       m_bossTex;
	S_Object        s_boss = {};
    const Math::Vector2	m_bossInitPos = { 400,60 };
	float           m_bossAnimCnt = {};
	float           m_bossHp = {};
	float           m_bossActionCnt = {};
	bool            m_ElementChangeFlg = {};
	bool            m_rotationAttackFlg = {};
	bool            m_homingAttackFlg = {};
	bool            m_bossMoveFlg = {};
	const float     m_bossRadius = 42;
	Math::Vector2   m_bossMoveTable[4] = { {2,2},{-2,2},{2,-2},{-2,-2} };
	float           m_bossMoveCnt = {};



	KdTexture        m_spikeEnemyTex;
	static const int spikeEnemyNum = 15;
	S_Object         s_spikeEnemy[spikeEnemyNum] = {};

	float            m_sEnemyDegTable[spikeEnemyNum] = { 0,24,48,72,96,120,144,168,192,216,240,264,288,312,336 };
	float            m_sEnemyDeg[spikeEnemyNum] = {};

	float            m_sEnemyAnimCnt[spikeEnemyNum] = {};  // アニメーション

	float            m_sEnemyMoveFlg[spikeEnemyNum] = {};  // 攻撃時用
	float            m_sEnemyMoveWait = {};                // 少しずつ敵を動かす
	float            m_sEnemyHp[spikeEnemyNum] = {}; 

	float            m_sEnemyFalseCnt={};
	
	const float      m_sEnemyMaxHp = 5;
	const float      m_sEnemyRadius = 32;
	float            m_sEnemySpawnCnt = {};
	float            m_homingCnt[spikeEnemyNum] = {};




	// トゲ型の敵　
	Math::Vector2    m_sEnemyAttackPos[spikeEnemyNum] = {};
	Math::Vector2    m_sEnemyAttackMove[spikeEnemyNum] = {};
	Math::Matrix     m_sEnemyAttackMat[spikeEnemyNum] = {};
	const float      m_AttackMoveSpeedX = -2;





	KdTexture        m_gearEnemyTex;
	static const int gearEnemyNum = 8;
	S_Object         s_gearEnemy[gearEnemyNum] = {};
	float            m_gEnemyDegTable[gearEnemyNum] = { 0, 45, 90, 135, 180, 225, 270, 315 };
	float            m_gEnemyDeg[gearEnemyNum] = {};
	float            m_gEnemyAnimCnt[gearEnemyNum] = {};
	float            m_gEnemyHp[gearEnemyNum] = {};
	float            m_gEnemyFalseCnt = {};
	const float      m_gEnemyMaxHp = 5;
	const float      m_gEnemyRadius = 32;
	float            m_gEnemySpawnCnt = {};



	std::shared_ptr<C_Player>m_player;
	
	std::shared_ptr<C_Explosion>m_gEnemyExplosion[gearEnemyNum];
	std::shared_ptr<C_Explosion>m_sEnemyExplosion[spikeEnemyNum];
};