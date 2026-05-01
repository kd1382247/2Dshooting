#include "Exhaust.h"

void C_Exhaust::Draw(bool a_flg)
{
	if (a_flg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle((int)m_animCnt * 96, 0, 96, 96), 1.0f);
	}
}

void C_Exhaust::Update(bool a_flg,Math::Vector2 a_pos)
{
	if (a_flg)
	{
		m_pos.x = a_pos.x - 38.0f;
		m_pos.y = a_pos.y;

		m_transMat = Math::Matrix::CreateTranslation(m_pos.x,m_pos.y, 0);
		m_rotationMat = Math::Matrix::CreateRotationZ(ToRadians(m_angle));

		m_mat = m_rotationMat * m_transMat;

		//排気アニメーション
		m_animCnt += 0.3f;
		if (m_animCnt > 5.0f)
		{
			m_animCnt = 0.0f;
		}
	}
}

void C_Exhaust::Init()
{
	m_tex.Load("Textures/Effect/exhaust.png");
	m_animCnt = 0.0f;
	m_pos = { 0.0f,0.0f };
	m_angle = 270.0f;

}

void C_Exhaust::Release()
{

}
