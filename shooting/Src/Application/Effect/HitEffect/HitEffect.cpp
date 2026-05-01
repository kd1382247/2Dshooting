#include "HitEffect.h"

void C_HitEffect::Draw()
{

	for(int i=0;i<collisionEfNum;i++)
	{
		if(s_collisionEf[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_collisionEf[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_collisionEfTex, Math::Rectangle((int)s_collisionEf[i].m_animCnt*60, 0, 60, 60), 1.0f);
		}
	}
}

void C_HitEffect::Update()
{

	for (int i = 0; i < collisionEfNum; i++)
	{
		if (s_collisionEf[i].m_aliveFlg)
		{			
			// アニメーション
			s_collisionEf[i].m_animCnt += 0.8;
			if (s_collisionEf[i].m_animCnt>9)
			{
				s_collisionEf[i].m_aliveFlg = false;
			}

			s_collisionEf[i].m_mat = Math::Matrix::CreateTranslation(s_collisionEf[i].m_pos.x, s_collisionEf[i].m_pos.y, 0);
		}
	}
}

void C_HitEffect::SpawnEffect(Math::Vector2 a_pos)
{
	for (int i = 0; i < collisionEfNum; i++)
	{
		if (!s_collisionEf[i].m_aliveFlg)
		{
			s_collisionEf[i].m_pos = a_pos;
			s_collisionEf[i].m_animCnt = 0.0f;
			s_collisionEf[i].m_aliveFlg = true;
			break;
		}
	}

}

void C_HitEffect::Init()
{
	m_collisionEfTex.Load("Textures/Effect/collisionEffect.png");
}

void C_HitEffect::Release()
{
	m_collisionEfTex.Release();
}
