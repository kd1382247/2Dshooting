#pragma once
#include"../BaseObject.h"


class C_HitEffect;

class C_Bullet:public C_BaseObject
{
public:


	C_Bullet() { Init(); }
	~C_Bullet()override { Release(); }


	void Draw();
	void Update();
	

	void Spawn(Math::Vector2 a_pos,Element a_nowElement);

	Math::Vector2 GetPos(int a_i) { return s_bullet[a_i].m_pos; }
	float         GetRadius() { return m_radius; }
	int           GetNum() { return bulletNum; }
	bool          GetAliveFlg(int a_i) { return s_bullet[a_i].m_aliveFlg; }
	void  SetHitFlg(int a_i, bool a_flg) { m_hitFlg[a_i] = a_flg; }

private:


	void Init();
	void Release();
	void Move();
	void AliveState();
	
	KdTexture        m_bulletTex;
	static const int bulletNum = 50;
	S_Object         s_bullet[bulletNum] = {};
	bool             m_hitFlg[bulletNum] = {};


	const float      m_bulletSpeed = 15.0f;

	int              m_shotWait;


	std::shared_ptr<C_HitEffect>m_hitEffect[bulletNum];

};