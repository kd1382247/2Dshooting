#pragma once

struct S_HitEffect
{
	Math::Vector2 m_pos;
	Math::Matrix  m_mat;
	float         m_animCnt;
	bool          m_aliveFlg;
};


class C_HitEffect
{
public:

	C_HitEffect() { Init(); }
	~C_HitEffect(){ Release(); }

	void Draw();
	void Update();
	void SpawnEffect(Math::Vector2 a_pos);

	
private:

	void Init();
	void Release();

	KdTexture          m_collisionEfTex;

	static const int   collisionEfNum = 50;
	S_HitEffect  s_collisionEf[collisionEfNum]{};

};