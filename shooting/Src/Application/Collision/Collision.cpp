#include "Collision.h"

#include"../Object/Player/Player.h"
#include"../Object/Bullet/Bullet.h"

#include"../Object/Enemy/GearEnemy/GearEnemy.h"
#include"../Object/Enemy/SpikeEnemy/SpikeEnemy.h"
#include"../Object/Enemy/RushEnemy/RushEnemy.h"


void C_Collision::Update()
{
	CheckBulletGearEnemy();
	CheckBulletSpikeEnemy();

	CheckPlayerGearEnemy();
	CheckPlayerSpikeEnemy();

	CheckBulletRushEnemy();
	CheckPlayerRushEnemy();

}

void C_Collision::CheckBulletGearEnemy()
{
	for (int i = 0; i < m_gearEnemy->GetNum(); i++)
	{
		for (int j = 0; j < m_bullet->GetNum(); j++)
		{
			if(m_gearEnemy->GetAliveFlg(i)&&m_bullet->GetAliveFlg(j))
			{
				Math::Vector2 pos = m_gearEnemy->GetPos(i) - m_bullet->GetPos(j);
				
				if (pos.Length() < m_gearEnemy->GetRadius() + m_bullet->GetRadius())
				{
					m_gearEnemy->damage(i);
					m_bullet->SetHitFlg(j, true);
				}
			}
		}
	}
}

void C_Collision::CheckPlayerGearEnemy()
{
	for (int i = 0; i < m_gearEnemy->GetNum(); i++)
	{
		if (m_gearEnemy->GetAliveFlg(i) && m_player->GetAliveFlg())
		{
			Math::Vector2 pos = m_player->GetPos() - m_gearEnemy->GetPos(i);
			

			if (pos.Length() < m_player->GetRadius() + m_gearEnemy->GetRadius())
			{
				m_gearEnemy->SetHp(0, i);
			}
		}
	}
}

void C_Collision::CheckBulletSpikeEnemy()
{
	for (int i = 0; i < m_spikeEnemy->GetNum(); i++)
	{
		for (int j = 0; j < m_bullet->GetNum(); j++)
		{
			if (m_spikeEnemy->GetAliveFlg(i) && m_bullet->GetAliveFlg(j))
			{
				Math::Vector2 pos = m_spikeEnemy->GetPos(i) - m_bullet->GetPos(j);

				if (pos.Length() < m_bullet->GetRadius() + m_spikeEnemy->GetRadius())
				{
					m_spikeEnemy->damage(i);
					m_bullet->SetHitFlg(j, true);
				}
			}
		}
	}

}

void C_Collision::CheckPlayerSpikeEnemy()
{
	for (int i = 0; i < m_spikeEnemy->GetNum(); i++)
	{
		if (m_spikeEnemy->GetAliveFlg(i) && m_player->GetAliveFlg())
		{
			Math::Vector2 pos = m_player->GetPos() - m_spikeEnemy->GetPos(i);


			if (pos.Length() < m_player->GetRadius() + m_spikeEnemy->GetRadius())
			{
				m_spikeEnemy->SetHp(0, i);
			}
		}
	}
}

void C_Collision::CheckBulletRushEnemy()
{
	
	for (int i = 0; i < m_rushEnemy->GetNum(); i++)
	{
		for (int j = 0; j < m_bullet->GetNum(); j++)
		{
			if (m_rushEnemy->GetAliveFlg(i) && m_bullet->GetAliveFlg(j))
			{
				Math::Vector2 pos = m_rushEnemy->GetPos(i) - m_bullet->GetPos(j);

				if (pos.Length() < m_bullet->GetRadius() + m_rushEnemy->GetRadius())
				{
					m_rushEnemy->damage(i);
					m_bullet->SetHitFlg(j, true);
				}
			}
		}
	}
}

void C_Collision::CheckPlayerRushEnemy()
{
	for (int i = 0; i < m_rushEnemy->GetNum(); i++)
	{
		if (m_rushEnemy->GetAliveFlg(i) && m_player->GetAliveFlg())
		{
			Math::Vector2 pos = m_player->GetPos() - m_rushEnemy->GetPos(i);


			if (pos.Length() < m_player->GetRadius() + m_rushEnemy->GetRadius())
			{
				m_rushEnemy->SetHp(0, i);
			}
		}
	}
}
