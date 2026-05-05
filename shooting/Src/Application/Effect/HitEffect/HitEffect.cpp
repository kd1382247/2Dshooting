#include "HitEffect.h"

void C_HitEffect::Draw()
{
	if (s_hitEffect.m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(s_hitEffect.m_mat);
		SHADER.m_spriteShader.DrawTex(&m_hitEffectTex, Math::Rectangle((int)s_hitEffect.m_animCnt * 60, 0, 60, 60), 1.0f);
	}
}

void C_HitEffect::Update()
{

	if (s_hitEffect.m_aliveFlg)
	{
		// アニメーション
		s_hitEffect.m_animCnt += 0.8;
		if (s_hitEffect.m_animCnt > 9)
		{
			s_hitEffect.m_aliveFlg = false;
		}

		s_hitEffect.m_mat = Math::Matrix::CreateTranslation(s_hitEffect.m_pos.x, s_hitEffect.m_pos.y, 0);
	}

}

void C_HitEffect::Spawn(Math::Vector2 a_pos)
{

	if (!s_hitEffect.m_aliveFlg)
	{
		s_hitEffect.m_pos = a_pos;
		s_hitEffect.m_animCnt = 0.0f;
		s_hitEffect.m_aliveFlg = true;
	}
}

void C_HitEffect::Init()
{
	m_hitEffectTex.Load("Textures/Effect/collisionEffect.png");
	s_hitEffect = {};
}

void C_HitEffect::Release()
{
	m_hitEffectTex.Release();
}
