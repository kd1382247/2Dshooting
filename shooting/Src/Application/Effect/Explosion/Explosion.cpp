#include "Explosion.h"

void C_Explosion::Draw()
{

	if (s_explosion.m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(s_explosion.m_mat);
		SHADER.m_spriteShader.DrawTex(&m_explosionTex, Math::Rectangle((int)s_explosion.m_animCnt * 150, 0, 150, 150), 1.0f);
	}

}

void C_Explosion::Update()
{

	if (s_explosion.m_aliveFlg)
	{
		s_explosion.m_animCnt += 0.4;
		if (s_explosion.m_animCnt > 11)
		{
			s_explosion.m_aliveFlg = false;
		}
		s_explosion.m_mat = Math::Matrix::CreateTranslation(s_explosion.m_pos.x, s_explosion.m_pos.y, 0);
	}

}

void C_Explosion::Spawn(Math::Vector2 a_pos)
{

	if (!s_explosion.m_aliveFlg)
	{
		s_explosion.m_aliveFlg = true;
		s_explosion.m_pos = a_pos;
		s_explosion.m_animCnt = 0;
	}

}

void C_Explosion::Init()
{
	m_explosionTex.Load("Textures/Effect/explosion.png");
	s_explosion = {};
}

void C_Explosion::Release()
{
	m_explosionTex.Release();
}
