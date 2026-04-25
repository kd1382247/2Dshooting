#pragma once
#include"Element.h"

struct S_Bullet
{
	Math::Vector2      m_pos;
	Math::Vector2      m_move;
	Math::Matrix       m_mat;
	bool               m_aliveFlg;
	Element            m_nowElement;
};



class C_Bullet
{
public:


	C_Bullet() { Init(); }
	~C_Bullet() { Release(); }


	void Draw();
	void Update();
	


	void SpawnBullet(Math::Vector2 a_pos,Element a_element);

private:

	void Init();
	void Release();
	void BulletMove();
	
	static const int bulletNum = 50;
	S_Bullet         s_bullet[bulletNum];
	KdTexture        m_bulletTex;

	const float      m_bulletSpeed = 15.0f;

	int              m_shotWait;
};