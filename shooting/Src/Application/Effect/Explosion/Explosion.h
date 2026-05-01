#pragma once

struct S_Explosion
{
	Math::Vector2 m_pos;
	Math::Matrix  m_mat;
	bool          m_aliveFlg;
	float         m_animCnt;
};

class C_Explosion
{

public:

	C_Explosion() { Init(); }
	~C_Explosion() { Release(); }

	void Draw();
	void Update();
	void Spawn(Math::Vector2 a_pos);


private:

	void Init();
	void Release();

	KdTexture        m_explosionTex;

	static const int explosionNum=50;
	S_Explosion      s_explosion[explosionNum]{};


};