#include "CollisionManager.h"

#include"../Object/Player/Player.h"
#include"../Object/Bullet/Bullet.h"
#include"../Object/Enemy/Enemy.h"
#include"../Effect/HitEffect/HitEffect.h"


void C_Collision::checkBulletEnemy()
{
	for (int i = 0; i < m_enemy->GetNum(); i++)
	{
		for (int j = 0; j < m_bullet->GetNum(); j++)
		{
			if(m_enemy->GetAliveFlg(i)&&m_bullet->GetAliveFlg(j))
			{
				Math::Vector2 pos = m_enemy->GetPos(i) - m_bullet->GetPos(j);
				
				if (pos.Length() < m_enemy->GetRadius() + m_bullet->GetRadius())
				{
					m_enemy->SetAliveFlg(i, false);
					m_bullet->SetAliveFlg(j, false);
					m_hitEffect->SpawnEffect(m_bullet->GetPos(j));
				}
			}
		}
	}
}

void C_Collision::checkPlayerEnemy()
{
	for (int i = 0; i < m_enemy->GetNum(); i++)
	{
		if (m_enemy->GetAliveFlg(i) && m_player->GetAliveFlg())
		{
			Math::Vector2 pos = m_player->GetPos() - m_enemy->GetPos(i);
			

			if (pos.Length() < m_player->GetRadius() + m_enemy->GetRadius())
			{
				m_enemy->SetAliveFlg(i, false);
			}
		}
	}
}
