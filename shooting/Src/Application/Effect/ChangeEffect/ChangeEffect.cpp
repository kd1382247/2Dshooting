#include "ChangeEffect.h"

void C_ChangeEffect::Draw()
{
	if (m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle((int)m_animCnt * 384, 0, 384, 384), 1.0f);
	}
}

void C_ChangeEffect::Update(Math::Vector2 a_pos,float a_scale)
{
	if (m_aliveFlg)
	{
		m_animCnt += 0.2;
		if (m_animCnt > 7.0f)
		{
			m_aliveFlg = false;
			m_animCnt = 0.0f;
		}

		m_pos = { a_pos.x - 5,a_pos.y };

		m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		m_scaleMat = Math::Matrix::CreateScale(a_scale, a_scale, 0);
		m_mat = m_scaleMat * m_transMat;
	}
}

void C_ChangeEffect::Init()
{
	m_tex.Load("Textures/Effect/changeEffect.png");
	m_aliveFlg = false;
	m_animCnt = 0.0f;
	m_pos = { 0.0f,0.0f };
}

void C_ChangeEffect::Release()
{
	m_tex.Release();
}
