#include "Bullet.h"

#include"../Player/Player.h"
void C_Bullet::Draw()
{
	for (int i = 0; i < bulletNum; i++)
	{
		if (s_bullet[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_bullet[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_bulletTex, Math::Rectangle((int)s_bullet[i].m_nowElement*12, 0, 12, 12), 1.0f);
		}
	}
}

void C_Bullet::Update()
{
	BulletMove();
}

void C_Bullet::Init()
{

	m_bulletTex.Load("Textures/Player/bullet.png");
	m_shotWait = 0;
	m_radius = 6.0f;
	
}

void C_Bullet::SpawnBullet()
{

	if(m_shotWait==0)
	{
		for (int i = 0; i < bulletNum; i++)
		{
			if (!s_bullet[i].m_aliveFlg)
			{
				s_bullet[i].m_aliveFlg = true;
				s_bullet[i].m_move = { m_bulletSpeed,0 };

				if (m_player->GetNowElement() == Element::Fire)s_bullet[i].m_nowElement = Element::Fire;
				if (m_player->GetNowElement() == Element::Water)s_bullet[i].m_nowElement = Element::Water;
				if (m_player->GetNowElement() == Element::Grass)s_bullet[i].m_nowElement = Element::Grass;

				
				s_bullet[i].m_pos = { m_player->GetPos().x + 20,m_player->GetPos().y };
				m_shotWait = 10;
				break;
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
