#pragma once
#include"../BaseObject.h"


class C_Player;


class C_Bullet:public C_BaseObject
{
public:


	C_Bullet() { Init(); }
	~C_Bullet()override { Release(); }


	void Draw();
	void Update();
	
	void SetInstance(std::shared_ptr<C_Player> a_player) { m_player = a_player; }

	void SpawnBullet();

	Math::Vector2 GetPos(int a_i) { return s_bullet[a_i].m_pos; }
	float         GetRadius() { return m_radius; }
	int           GetNum() { return bulletNum; }
	bool          GetAliveFlg(int a_i) { return s_bullet[a_i].m_aliveFlg; }
	void  SetAliveFlg(int a_i, bool a_flg) { s_bullet[a_i].m_aliveFlg = a_flg; }

private:

	std::shared_ptr<C_Player>m_player;

	void Init();
	void Release();
	void BulletMove();
	
	static const int bulletNum = 50;
	S_Object         s_bullet[bulletNum] = {};
	KdTexture        m_bulletTex;

	const float      m_bulletSpeed = 15.0f;


	int              m_shotWait;
};