#pragma once
#include"../../BaseObject.h"

class C_Exhaust;
class C_Explosion;


class C_ShotEnemy :public C_BaseObject
{
public:


	struct S_EnemyBullet
	{
		Math::Vector2 m_pos;
		Math::Vector2 m_move;
		Math::Matrix  m_mat;
		bool          m_aliveFlg;
		bool          m_radius;
		Element       m_nowElement;
	};

	C_ShotEnemy() { Init(); }
	~C_ShotEnemy() override{ Release(); }

	void Draw()override;
	void Update()override;
	void Spawn();


	// 当たり判定クラスで呼び出す関数
	Math::Vector2 GetPos(int a_i) { return s_shotEnemy[a_i].m_pos; }
	float         GetRadius() { return m_radius; }
	int           GetNum() { return shotEnemyNum; }
	bool          GetAliveFlg(int a_i) { return s_shotEnemy[a_i].m_aliveFlg; }
	void damage(int a_i) { m_hp[a_i]--; }
	void SetHp(int a_hp, int a_i) { m_hp[a_i] = a_hp; }

private:

	void Init()override;
	void Release()override;

	void MoveEnemy();
	void AliveState();
	void Shot(Math::Vector2 a_pos,Element a_nowElemet);

	void MoveBullet();

	KdTexture m_shotEnemyTex;
	static const int shotEnemyNum = 12;
	S_Object  s_shotEnemy[shotEnemyNum] = {};

	// 弾
	KdTexture        m_enemyBulletTex;
	static const int enemyBulletNum = 24;
	S_EnemyBullet    s_enemyBullet[enemyBulletNum] = {};
	const float      m_bulletMoveSpeed = -5;
	

	const float      m_moveSpeedX = -1.5f;

	float            m_hp[shotEnemyNum] = {};
	

	// 排気エフェクト
	std::shared_ptr<C_Exhaust>m_exhaust[shotEnemyNum];
	const float               m_exhaustAngle = 90.0f;


	std::shared_ptr<C_Explosion>m_explosion[shotEnemyNum];

};
