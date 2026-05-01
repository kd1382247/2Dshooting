#include "Explosion.h"

void C_Explosion::Draw()
{

	for(int i=0;i<explosionNum;++i)
	{
		if(s_explosion[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_explosion[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_explosionTex, Math::Rectangle(s_explosion[i].m_animCnt*90, 0, 90, 90), 1.0f);
		}
	}
}

void C_Explosion::Update()
{
	for (int i = 0; i < explosionNum; ++i)
	{
		if (s_explosion[i].m_aliveFlg)
		{
			s_explosion[i].m_animCnt += 0.6;
			if (s_explosion[i].m_animCnt > 11)
			{
				s_explosion[i].m_aliveFlg = false;
			}
			s_explosion[i].m_mat = Math::Matrix::CreateTranslation(s_explosion[i].m_pos.x, s_explosion[i].m_pos.y, 0);
		}
	}
}

void C_Explosion::Spawn(Math::Vector2 a_pos)
{
	for (int i = 0; i < explosionNum; ++i)
	{
		if (!s_explosion[i].m_aliveFlg)
		{
			s_explosion[i].m_aliveFlg = true;
			s_explosion[i].m_pos = a_pos;
			s_explosion[i].m_animCnt = 0;
			break;
		}
	}
}

void C_Explosion::Init()
{
	m_explosionTex.Load("Textures/Effect/explosion.png");
}

void C_Explosion::Release()
{
	m_explosionTex.Release();
}
