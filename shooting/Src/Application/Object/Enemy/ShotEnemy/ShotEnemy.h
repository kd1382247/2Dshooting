#pragma once
#include"../../BaseObject.h"

class C_Exhaust;
class C_Explosion;
class C_EnemyBullet;

class C_ShotEnemy :public C_BaseObject
{
public:


	

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

	void SetInstance(std::shared_ptr<C_EnemyBullet>a_enemyBullet) { m_enemyBullet = a_enemyBullet; }

private:

	void Init()override;
	void Release()override;

	void Move();
	void AliveState();
	void Action();




	KdTexture m_shotEnemyTex;
	static const int shotEnemyNum = 12;
	S_Object  s_shotEnemy[shotEnemyNum] = {};
	bool      m_shotFlg[shotEnemyNum] = {};
	float     m_shotWait[shotEnemyNum] = {};
	int       m_shotCnt[shotEnemyNum] = {};
	float     m_coolTime[shotEnemyNum] = {};

	const float      m_moveSpeedX = -1.0f;

	float            m_hp[shotEnemyNum] = {};
	

	// 排気エフェクト
	std::shared_ptr<C_Exhaust>m_exhaust[shotEnemyNum];
	const float               m_exhaustAngle = 90.0f;
	const float               m_exhaustDistance = 38;


	std::shared_ptr<C_Explosion>m_explosion[shotEnemyNum];

	std::shared_ptr<C_EnemyBullet>m_enemyBullet;


};
