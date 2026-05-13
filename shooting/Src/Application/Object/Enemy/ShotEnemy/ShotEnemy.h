#pragma once
#include"../../BaseObject.h"

class C_Exhaust;
class C_Explosion;
class C_EnemyBullet;
class C_Score;
class C_Player;

class C_ShotEnemy :public C_BaseObject
{
public:

	C_ShotEnemy() { Init(); }
	~C_ShotEnemy() override{ Release(); }

	void Draw()override;
	void Update()override;
	void Spawn();
	bool GetAliveFalseFlg() { return m_aliveFalseFlg; }

	void SetInstance(std::shared_ptr<C_EnemyBullet>a_enemyBullet,
						 std::shared_ptr<C_Score>a_score,
						 std::shared_ptr<C_Player>a_player) 
						{ 
							m_enemyBullet = a_enemyBullet;
							m_score = a_score;
							m_player = a_player;
						}


	// 当たり判定クラスで呼び出す関数
	Math::Vector2 GetPos(int a_i)                 { return s_shotEnemy[a_i].m_pos; }
	float         GetRadius()                     { return m_radius; }
	int           GetNum()                        { return shotEnemyNum; }
	Element       GetElement(int a_i)             { return s_shotEnemy[a_i].m_nowElement; }
	bool          GetAliveFlg(int a_i)            { return s_shotEnemy[a_i].m_aliveFlg; }
	float         GetAttackPow()                  { return m_attackPow; }
	void          Damage(int a_i, float a_damage) { m_hp[a_i]-=a_damage; }

	void          SetMatchupType(int a_i, MatchupType a_matchupType) { e_matchupType[a_i] = a_matchupType; }
	float         GetScore(MatchupType a_matchupType);

private:

	void Init()override;
	void Release()override;

	void Move();
	void AliveState();
	void Action();


	KdTexture        m_shotEnemyTex;
	static const int shotEnemyNum = 14;
	S_Object         s_shotEnemy[shotEnemyNum] = {};
	bool             m_shotFlg[shotEnemyNum] = {};
	float            m_shotWait[shotEnemyNum] = {};
	int              m_shotCnt[shotEnemyNum] = {};
	float            m_coolTime[shotEnemyNum] = {};
	MatchupType      e_matchupType[shotEnemyNum] = {};


	float            m_aliveFalseCnt = {};
	bool             m_aliveFalseFlg = {};

	const float      m_moveSpeedX = -1.5f;
	const float      m_attackPow = 10;
	float            m_hp[shotEnemyNum] = {};
	const float      m_maxHp = 100;
	
	int              m_randomElement = {};

	const float      shotEnemyScore = 30000;

	// 排気エフェクト
	std::shared_ptr<C_Exhaust>m_exhaust[shotEnemyNum];
	const float               m_exhaustAngle = 90.0f;
	const float               m_exhaustDistance = 38;


	std::shared_ptr<C_Explosion>  m_explosion[shotEnemyNum];

	std::shared_ptr<C_EnemyBullet>m_enemyBullet;

	std::shared_ptr<C_Score>m_score;

	std::shared_ptr<C_Player>m_player;

};
