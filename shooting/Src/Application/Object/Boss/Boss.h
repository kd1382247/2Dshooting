#pragma once
#include"../BaseObject.h"

class C_Player;
class C_Explosion;
class C_ChangeEffect; 


class C_Boss :public C_BaseObject
{

public:

	struct S_Warning
	{
		Math::Matrix  m_mat;
		Math::Vector2 m_pos = {};
		Math::Vector2 m_move = {};
		bool          m_aliveFlg = {};
	};

	struct S_Shield
	{
		Math::Matrix  m_mat;
		Math::Vector2 m_pos = {};
		bool          m_aliveFlg = {};
		bool          m_shieldReleaseFlg = {};
		Math::Vector2 m_animCnt = {};
	};


	C_Boss() { Init(); }
	~C_Boss()override { Release(); }

	void Draw()override;
	void Update()override;

	void SpawnBoss();

	void SetInstance(std::shared_ptr<C_Player>a_player) { m_player = a_player; }


	// 当たり判定クラスで呼び出す関数(トゲ型の敵)
	Math::Vector2 SEnemyGetPos(int a_i)                  { return s_spikeEnemy[a_i].m_pos; }
	float         SEnemyGetRadius()                      { return m_sEnemyRadius; }
	float         SEnemyGetAttackPow()                   { return m_sEnemyAttackPow; }
	int           SEnemyGetNum()                         { return spikeEnemyNum; }
	bool          SEnemyGetAliveFlg(int a_i)             { return s_spikeEnemy[a_i].m_aliveFlg; }
	void          SEnemyDamage(int a_i,float a_damage)   { m_sEnemyHp[a_i]-=a_damage; }
	Element       SEnemyGetElement(int a_i)              { return s_spikeEnemy[a_i].m_nowElement; }
	void          SEnemySetHomingFlg(int a_i,bool a_flg) { m_homingFlg[a_i]=a_flg; }
	bool          SEnemyGetHomingFlg(int a_i)            { return m_homingFlg[a_i]; }


	// 当たり判定クラスで呼び出す関数(歯車型の敵)
	Math::Vector2 GEnemyGetPos(int a_i)                  { return s_gearEnemy[a_i].m_pos; }
	float         GEnemyGetRadius()                      { return m_gEnemyRadius; }
	float         GEnemyGetAttackPow()                   { return m_gEnemyAttackPow; }
	void          GEnemyDamage(int a_i, float a_damage)  { m_gEnemyHp[a_i] -= a_damage; }
	int           GEnemyGetNum()                         { return gearEnemyNum; }
	bool          GEnemyGetAliveFlg(int a_i)             { return s_gearEnemy[a_i].m_aliveFlg; }
	Element       GEnemyGetElement(int a_i)				 { return s_gearEnemy[a_i].m_nowElement; }
	


	// 当たり判定クラスで呼び出す関数(ボス)
	Math::Vector2 BossGetPos()                           { return s_boss.m_pos; }
	float         BossGetRadius()                        { return m_bossRadius; }
	float         BossGetAttackPow()                     { return m_bossAttackPow; }
	bool          BossGetAliveFlg()                      { return s_boss.m_aliveFlg; }
	void          BossDamage(float a_damage)             { m_bossHp-=a_damage; }
	Element       BossGetElement()                       { return s_boss.m_nowElement; }

	// 当たり判定クラスで呼び出す関数(シールド)
	Math::Vector2 ShieldGetPos()                         { return s_shield.m_pos; }
	float         ShieldGetRadius()                      { return m_shieldRadius; }
	bool          ShieldGetAliveFlg()                    { return s_shield.m_aliveFlg; }


private:

	void Init()override;
	void Release()override;
	 
	// ボス
	void DrawBoss();
	void MoveBoss();
	void InitBoss();
	void Action();
	void SetBossMove();
	void ElementChange();
	
	// シールド
	void DrawShield();
	void UpdateShield();
	void InitShield();

	// トゲ型の敵
	void DrawSpikeEnemy();
	void MoveSpikeEnemy();
	void InitSpikeEnemy();
	void AliveStateSpikeEnemy();
	void SpawnSpikeEnemy();

	//　トゲ型の敵警告画像
	void DrawSEnemyWarning();
	void UpdateSEnemyWarning();
	void AliveStateSEWarning();
	void SpawnSEWarning();

	// 歯車型の敵
	void DrawGearEnemy();
	void MoveGearEnemy();
	void InitGearEnemy();
	void AliveStateGearEnemy();
	void SpawnGearEnemy();

	// 歯車型の敵の警告画像
	void DrawGEnemyWarning();
	void UpdateGEnemyWarning();
	void AliveStateGEWarning();
	void SpawnGEWarning();

	
	// ボス
	KdTexture       m_bossTex;
	S_Object        s_boss = {};
    const Math::Vector2	m_bossInitPos = { 400,60 };
	float           m_bossAnimCnt = {};
	const float     m_bossMaxHp = 1000;
	float           m_bossHp = {};
	float           m_bossActionCnt = {};
	bool            m_rotationAttackFlg = {};
	bool            m_homingAttackFlg = {};
	bool            m_bossMoveFlg = {};
	const float     m_bossRadius = 42;
	float           m_bossMoveCnt = {};
	float           m_enemySpawnCnt = {};
    float           m_bossAttackPow = 10;



	// ボスのシールド
	KdTexture   m_shieldTex;
	S_Shield    s_shield = {};
	const float m_shieldRadius = 50;



	// トゲ型の敵の変数
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
	
	const float      m_sEnemyMaxHp = 60;
	const float      m_sEnemyRadius = 32;
	const float      m_sEnemyAttackPow = 8;
	float            m_sEnemySpawnCnt = {};
	float            m_homingCnt[spikeEnemyNum] = {};
	float            m_homingFlg[spikeEnemyNum] = {};


	// トゲ型の敵が攻撃時に使用　
	Math::Vector2    m_sEnemyAttackPos[spikeEnemyNum] = {};
	Math::Vector2    m_sEnemyAttackMove[spikeEnemyNum] = {};
	Math::Matrix     m_sEnemyAttackMat[spikeEnemyNum] = {};
	const float      m_AttackMoveSpeedX = -2;
	
	
	// 歯車型の敵の変数
	KdTexture        m_gearEnemyTex;
	static const int gearEnemyNum = 8;
	S_Object         s_gearEnemy[gearEnemyNum] = {};
	float            m_gEnemyDegTable[gearEnemyNum] = { 0, 45, 90, 135, 180, 225, 270, 315 };
	float            m_gEnemyDeg[gearEnemyNum] = {};
	float            m_gEnemyAnimCnt[gearEnemyNum] = {};
	float            m_gEnemyHp[gearEnemyNum] = {};
	float            m_gEnemyFalseCnt = {};
	const float      m_gEnemyMaxHp = 80;
	const float      m_gEnemyRadius = 32;
	const float      m_gEnemyAttackPow = 8;
	float            m_gEnemySpawnCnt = {};


	// 警告画像
	KdTexture     m_warningTex;
	
	// 歯車型の敵用警告画像
	S_Warning     s_gEWarning[gearEnemyNum] = {};
	float         m_gEWarningDeg[gearEnemyNum] = {};
	float         m_gEFlashCnt = {};
	float         m_gEAlpha = {};
	float         m_gEWarningCnt = {};
	bool          m_gEWarningFlg = {};

	// トゲ型の敵用警告画像
	S_Warning     s_sEWarning[spikeEnemyNum] = {};
	float         m_sEWarningDeg[spikeEnemyNum] = {};
	float         m_sEFlashCnt = {};
	float         m_sEAlpha = {};
	float         m_sEWarningCnt = {};
	bool          m_sEWarningFlg = true;


	//
	std::shared_ptr<C_Player>m_player;
	
	// 属性チェンジエフェクト
	std::shared_ptr<C_ChangeEffect>m_changeEffect;

	// 爆破エフェクト
	std::shared_ptr<C_Explosion>m_gEnemyExplosion[gearEnemyNum];
	std::shared_ptr<C_Explosion>m_sEnemyExplosion[spikeEnemyNum];
};