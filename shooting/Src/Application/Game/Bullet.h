#pragma once
#include"../Base/BaseObject.h"


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

private:

	std::shared_ptr<C_Player>m_player;

	void Init();
	void Release();
	void BulletMove();
	
	static const int bulletNum = 50;
	S_Object         s_bullet[bulletNum];
	KdTexture        m_bulletTex;

	const float      m_bulletSpeed = 15.0f;

	int              m_shotWait;
};