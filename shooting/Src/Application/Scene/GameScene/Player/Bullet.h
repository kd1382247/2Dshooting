#pragma once



struct S_Bullet
{
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Matrix  m_mat;

	bool          m_aliveFlg;
};

class C_Bullet
{
public:


	C_Bullet() { Init(); }
	~C_Bullet() { Release(); }


	void Draw(int a_nowElement);
	void Update();
	void Init();


	void SpawnBullet(Math::Vector2 a_pos);

private:


	void Release();
	void BulletMove();
	
	static const int bulletNum = 50;
	S_Bullet         s_bullet[bulletNum];
	KdTexture        m_bulletTex;

	const float      m_bulletSpeed = 15.0f;

	int              m_shotWait;
};