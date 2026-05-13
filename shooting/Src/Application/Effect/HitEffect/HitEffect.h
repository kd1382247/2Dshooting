#pragma once
#include"../../Data/Element/Element.h"

struct S_HitEffect
{
	Math::Vector2 m_pos;
	Math::Matrix  m_mat;
	float         m_animCnt;
	Element       m_nowElement;
	bool          m_aliveFlg;
};


class C_HitEffect
{
public:

	C_HitEffect() { Init(); }
	~C_HitEffect(){ Release(); }

	void Draw();
	void Update();
	void Spawn(Math::Vector2 a_pos,Element a_element);

	
private:

	void Init();
	void Release();

	KdTexture    m_hitEffectTex;

	S_HitEffect  s_hitEffect={};

};