#include "Bullet.h"

#include"Player.h"
void C_Bullet::Draw()
{
	for (int i = 0; i < bulletNum; i++)
	{
		if (s_bullet[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_bullet[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_bulletTex, Math::Rectangle((int)s_bullet[i].m_nowElement*22, 0, 22, 6), 1.0f);
		}
	}
}

void C_Bullet::Update()
{
	BulletMove();
}

void C_Bullet::Init()
{

	m_bulletTex.Load("Textures/Player/bullet1.png");
	m_shotWait = 0;

	for (int i = 0; i < bulletNum; i++)
	{
		s_bullet[i].m_pos = { 0,0 };
		s_bullet[i].m_move = { 0,0 };
		s_bullet[i].m_aliveFlg = false;
	}
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

				if (i % 2 != 0)
				{
					s_bullet[i].m_pos = { m_player->GetPos().x ,m_player->GetPos().y + 20};
					m_shotWait = 10;
					break;
				}
				else if(i%2==0)
				{
					s_bullet[i].m_pos = { m_player->GetPos().x ,m_player->GetPos().y - 20 };
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
