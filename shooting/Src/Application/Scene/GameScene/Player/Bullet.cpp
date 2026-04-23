#include "Bullet.h"

void C_Bullet::Draw()
{
	for (int i = 0; i < bulletNum; i++)
	{
		if (s_bullet[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_bullet[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_bulletTex, Math::Rectangle(2*22, 0, 22, 10), 1.0f);
		}
	}
}

void C_Bullet::Update()
{
	BulletMove();
}

void C_Bullet::Init()
{

	m_bulletTex.Load("Textures/player/bullet1.png");
	m_shotWait = 0;

	for (int i = 0; i < bulletNum; i++)
	{
		s_bullet[i].m_pos = { 0,0 };
		s_bullet[i].m_move = { 0,0 };
		s_bullet[i].m_aliveFlg = false;
	}
}

void C_Bullet::SpawnBullet(Math::Vector2 a_pos)
{

	if(m_shotWait==0)
	{
		for (int i = 0; i < bulletNum; i++)
		{
			if (!s_bullet[i].m_aliveFlg)
			{
				s_bullet[i].m_aliveFlg = true;
				s_bullet[i].m_move = { m_bulletSpeed,0 };

				if (i % 2 != 0)
				{
					s_bullet[i].m_pos = { a_pos.x ,a_pos.y + 20 };
					m_shotWait = 10;
					break;
				}
				else if(i%2==0)
				{
					s_bullet[i].m_pos = { a_pos.x ,a_pos.y - 20 };
				}
				
			}
		}
	}

}

void C_Bullet::Release()
{
	m_bulletTex.Release();
}

void C_Bullet::BulletMove()
{
	
	m_shotWait--;
	if (m_shotWait < 0)
	{
		m_shotWait = 0;
	}

	for (int i = 0; i < bulletNum; i++)
	{
		if (s_bullet[i].m_aliveFlg)
		{
			if (s_bullet[i].m_pos.x >= 640 + 22)
			{
				s_bullet[i].m_aliveFlg = false;
			}
		}
	}

	//弾の移動処理
	for (int i = 0; i < bulletNum; i++)
	{
		if (s_bullet[i].m_aliveFlg)
		{
			s_bullet[i].m_pos += s_bullet[i].m_move;
			s_bullet[i].m_mat = Math::Matrix::CreateTranslation(s_bullet[i].m_pos.x, s_bullet[i].m_pos.y, 0);
		}
	}

}
