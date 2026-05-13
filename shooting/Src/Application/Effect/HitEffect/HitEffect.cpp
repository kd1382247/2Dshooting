#include "HitEffect.h"

void C_HitEffect::Draw()
{
	if (s_hitEffect.m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(s_hitEffect.m_mat);
		SHADER.m_spriteShader.DrawTex(&m_hitEffectTex, Math::Rectangle((int)s_hitEffect.m_animCnt * 64, s_hitEffect.m_nowElement*64, 64, 64), 1.0f);
	}
}

void C_HitEffect::Update()
{

	if (s_hitEffect.m_aliveFlg)
	{
		// アニメーション
		s_hitEffect.m_animCnt += 0.2;
		if (s_hitEffect.m_animCnt > 4)
		{
			s_hitEffect.m_aliveFlg = false;
		}

		s_hitEffect.m_mat = Math::Matrix::CreateTranslation(s_hitEffect.m_pos.x, s_hitEffect.m_pos.y, 0);
	}

}

void C_HitEffect::Spawn(Math::Vector2 a_pos,Element a_element)
{

	if (!s_hitEffect.m_aliveFlg)
	{
		s_hitEffect.m_pos = a_pos;
		s_hitEffect.m_animCnt = 0.0f;
		s_hitEffect.m_aliveFlg = true;
		s_hitEffect.m_nowElement = a_element;
	}
}

void C_HitEffect::Init()
{
	m_hitEffectTex.Load("Textures/Effect/hitEffect.png");
	s_hitEffect = {};
}

void C_HitEffect::Release()
{
	m_hitEffectTex.Release();
}
