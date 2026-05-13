#include "EnemyBullet.h"

#include"../../../Effect/HitEffect/HitEffect.h"

void C_EnemyBullet::Draw()
{
	// 弾
	for (int i = 0; i < bulletNum; i++)
	{
		if (s_bullet[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_bullet[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_bulletTex, Math::Rectangle((int)s_bullet[i].m_nowElement * 12, 0, 12, 12), 1.0f);
		}
	}

	for (int i = 0; i < bulletNum; i++)
	{
		m_hitEffect[i]->Draw();
	}

}

void C_EnemyBullet::Update()
{
	AliveState();
	Move();

	for (int i = 0; i < bulletNum; i++)
	{
		m_hitEffect[i]->Update();
	}
}

void C_EnemyBullet::Spawn(Math::Vector2 a_pos,Element a_nowElement)
{
	for (int i = 0; i < bulletNum; i++)
	{
		if (!s_bullet[i].m_aliveFlg)
		{
			s_bullet[i].m_aliveFlg = true;
			s_bullet[i].m_pos.x = a_pos.x - m_bulletDistance;
			s_bullet[i].m_pos.y = a_pos.y;
			s_bullet[i].m_nowElement = a_nowElement;
			s_bullet[i].m_move = { m_bulletMoveSpeed,0 };
			m_hitFlg[i] = false;
			break;
		}
	}
}

void C_EnemyBullet::Init()
{
	m_bulletTex.Load("Textures/Enemy/bullet.png");

	for (int i = 0; i < bulletNum; i++)
	{
		m_hitEffect[i] = std::make_shared<C_HitEffect>();
	}

	m_radius = 6;
}

void C_EnemyBullet::Release()
{
	m_bulletTex.Release();
}

void C_EnemyBullet::Move()
{
	
	// 行列作成
	for (int i = 0; i < bulletNum; i++)
	{
		if (s_bullet[i].m_aliveFlg)
		{
			s_bullet[i].m_pos += s_bullet[i].m_move;

			s_bullet[i].m_mat = Math::Matrix::CreateTranslation(s_bullet[i].m_pos.x, s_bullet[i].m_pos.y, 0);
		}
	}


}

void C_EnemyBullet::AliveState()
{

	for (int i = 0; i < bulletNum; i++)
	{
		if (s_bullet[i].m_aliveFlg)
		{
			if (s_bullet[i].m_pos.x < -640)
			{
				s_bullet[i].m_aliveFlg = false;
			}
		}

	}

	for (int i = 0; i < bulletNum; i++)
	{
		if (s_bullet[i].m_aliveFlg)
		{
			if (m_hitFlg[i])
			{
				s_bullet[i].m_aliveFlg = false;

				m_hitEffect[i]->Spawn(s_bullet[i].m_pos,s_bullet[i].m_nowElement);
			}
		}
	}

}
