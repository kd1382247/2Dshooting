#include "Bullet.h"


#include"../../Effect/HitEffect/HitEffect.h"
#include"../../Effect/DamagePopup/DamagePopup.h"


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


	for (int i = 0; i < bulletNum; i++)
	{
		m_hitEffect[i]->Draw();

		m_DamagePopup[i]->Draw();
	}
}

void C_Bullet::Update()
{
	AliveState();
	Move();

	
	for (int i = 0; i < bulletNum; i++)
	{
		m_hitEffect[i]->Update();

		m_DamagePopup[i]->Update();
	}
}

void C_Bullet::Init()
{

	m_bulletTex.Load("Textures/Player/bullet.png");
	m_shotWait = 0;
	m_radius = 6.0f;

	for (int i = 0; i < bulletNum; i++)
	{
		// ヒットエフェクト
		m_hitEffect[i] = std::make_shared<C_HitEffect>();
		// 属性相性エフェクト
		m_DamagePopup[i] = std::make_shared<C_DamagePopup>();
	}

}

void C_Bullet::Spawn(Math::Vector2 a_pos,Element a_nowElement)
{

	if(m_shotWait==0)
	{
		for (int i = 0; i < bulletNum; i++)
		{
			if (!s_bullet[i].m_aliveFlg)
			{
				s_bullet[i].m_aliveFlg = true;
				s_bullet[i].m_move = { m_bulletSpeed,0 };

				s_bullet[i].m_nowElement = a_nowElement;
				
				s_bullet[i].m_pos = { a_pos.x + 20,a_pos.y };
				m_hitFlg[i] = false;
				m_shieldHitFlg[i] = false;
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

void C_Bullet::Move()
{
	
	m_shotWait--;
	if (m_shotWait < 0)
	{
		m_shotWait = 0;
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

void C_Bullet::AliveState()
{
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

	for (int i = 0; i < bulletNum; i++)
	{
		if (s_bullet[i].m_aliveFlg)
		{
			if (m_hitFlg[i])
			{
				s_bullet[i].m_aliveFlg = false;

				m_hitEffect[i]->Spawn(s_bullet[i].m_pos,s_bullet[i].m_nowElement);

				// ボスのシールドに当たった場合表示しない
				if(!m_shieldHitFlg[i])
				{
					m_DamagePopup[i]->Spawn(s_bullet[i].m_pos,e_bulletMatchupType[i]);
				}
			}
		}
	}
}
