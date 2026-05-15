#pragma once

#include"../../BaseObject.h"

class C_Exhaust;
class C_Explosion;
class C_Score;
class C_Player;

class C_RushEnemy :public C_BaseObject
{
public:

	enum EnemyMotion
	{
		MinLeftMove = 1,
		MaxLeftMove = 0,
		Idle = 2,
		MinRightMove = 3,
		MaxRightMove = 4,
	};

	enum RLMove
	{
		Right,
		Left
	};

	struct S_Move
	{
		float         m_rightMoveCnt;
		float         m_leftMoveCnt;
		bool          m_rightMoveFlg;
		bool          m_leftMoveFlg;
	};

	C_RushEnemy() { Init(); }
	~C_RushEnemy()override { Release(); }

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
	Math::Vector2 GetPos(int a_i)                 { return s_rushEnemy[a_i].m_pos; }
	float         GetRadius()                     { return m_radius; }
	float         GetAttackPow()                  { return m_attackPow; }
	int           GetNum()                        { return rushEnemyNum; }
	Element       GetElement(int a_i)             { return s_rushEnemy[a_i].m_nowElement; }
	bool          GetAliveFlg(int a_i)            { return s_rushEnemy[a_i].m_aliveFlg; }
	void          Damage(int a_i, float a_damage) { m_hp[a_i]-=a_damage; }

	void          SetMatchupType(int a_i, MatchupType a_matchupType) { e_matchupType[a_i] = a_matchupType; }
	float         GetScore(MatchupType a_matchupType);

private:

	void Init()override;
	void Release()override;
	void Move();
	void AliveState();
	void MovePattern();


	KdTexture        m_rushEnemyTex;
	static const int rushEnemyNum = 18;
	S_Object         s_rushEnemy[rushEnemyNum] = {};
	EnemyMotion      e_enemyMotion[rushEnemyNum] = {};
	RLMove           e_rlMove[rushEnemyNum];
	MatchupType      e_matchupType[rushEnemyNum] = {};

	// 左右のアニメーションを管理する変数
	S_Move           s_move[rushEnemyNum] = {};

	const float      m_moveSpeedX = 1.5f;
	const float      m_moveSpeedY = 2.0f;

	float            m_hp[rushEnemyNum] = {};
	const float      m_maxHp = 100;
	const float      m_attackPow = 10;

	float            m_aliveFalseCnt = {};
	bool             m_aliveFalseFlg = {};

	int              m_randomElement = {};

	const float      rushEnemyScore = 20000;

	// 行動パターン
	float            m_moveCnt[rushEnemyNum] = {};

	bool             m_spawnFlg = {};

	// 排気エフェクト
	std::shared_ptr<C_Exhaust>m_exhaust[rushEnemyNum];
	const float               m_exhaustAngle=90.0f;


	std::shared_ptr<C_Explosion>m_explosion[rushEnemyNum];

	std::shared_ptr<C_Score>m_score;

	std::shared_ptr<C_Player>m_player;
};