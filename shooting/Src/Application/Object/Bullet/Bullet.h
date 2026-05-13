#pragma once
#include"../BaseObject.h"


class C_HitEffect;
class C_DamagePopup;

class C_Bullet:public C_BaseObject
{
public:


	C_Bullet() { Init(); }
	~C_Bullet()override { Release(); }


	void Draw();
	void Update();
	

	void Spawn(Math::Vector2 a_pos,Element a_nowElement);

	Math::Vector2 GetPos(int a_i)					      { return s_bullet[a_i].m_pos; }
	float         GetRadius()						      { return m_radius; }
	float         GetAttackPow()                          { return m_attackPow; }
	int           GetNum()							      { return bulletNum; }
	bool          GetAliveFlg(int a_i)				      { return s_bullet[a_i].m_aliveFlg; }
	Element       GetElement(int a_i)                     { return s_bullet[a_i].m_nowElement; }
	void          SetHitFlg(int a_i, bool a_flg)          { m_hitFlg[a_i] = a_flg; }
	void          SetShieldHitFlg(int a_i, bool a_flg)    { m_shieldHitFlg[a_i] = a_flg; }
	void          SetMatchupType(int a_i, MatchupType a_type) { e_bulletMatchupType[a_i] = a_type; }

private:


	void Init();
	void Release();
	void Move();
	void AliveState();
	
	KdTexture        m_bulletTex;
	static const int bulletNum = 50;
	S_Object         s_bullet[bulletNum] = {};
	bool             m_hitFlg[bulletNum] = {};
	MatchupType      e_bulletMatchupType[bulletNum] = {};

	bool             m_shieldHitFlg[bulletNum] = {};

	const float      m_bulletSpeed = 15.0f;
	const float      m_attackPow = 10;
	int              m_shotWait;


	std::shared_ptr<C_HitEffect>m_hitEffect[bulletNum];

	std::shared_ptr<C_DamagePopup>m_DamagePopup[bulletNum];

};