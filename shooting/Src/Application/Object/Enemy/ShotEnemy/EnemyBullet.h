#pragma once
#include"../../BaseObject.h"

class C_HitEffect;

class C_EnemyBullet :public C_BaseObject
{
public:


	struct S_EnemyBullet
	{
		Math::Vector2 m_pos;
		Math::Vector2 m_move;
		Math::Matrix  m_mat;
		bool          m_aliveFlg;
		Element       m_nowElement;
	};

	C_EnemyBullet() { Init(); }
	~C_EnemyBullet() { Release(); }


	void Draw()override;
	void Update()override;

	void Spawn(Math::Vector2 a_pos,Element a_nowElement);


	// 当たり判定クラスで呼び出す関数
	Math::Vector2 GetPos(int a_i) { return s_bullet[a_i].m_pos; }
	float         GetRadius() { return m_radius; }
	int           GetNum() { return bulletNum; }
	bool          GetAliveFlg(int a_i) { return s_bullet[a_i].m_aliveFlg; }
	void  SetHitFlg(int a_i, bool a_flg) { m_hitFlg[a_i] = a_flg; }

private:

	void Init()override;
	void Release()override;
	void Move();
	void AliveState();

	// 弾
	KdTexture        m_bulletTex;
	static const int bulletNum = 30;
	S_EnemyBullet    s_bullet[bulletNum] = {};
	const float      m_bulletMoveSpeed = -5;
	const float      m_bulletDistance = 30;
	bool             m_hitFlg[bulletNum] = {};

	std::shared_ptr<C_HitEffect>m_hitEffect[bulletNum];

};


