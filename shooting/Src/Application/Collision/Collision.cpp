#include "Collision.h"

#include"../Object/Player/Player.h"
#include"../Object/Bullet/Bullet.h"
#include"../Object/Enemy/ShotEnemy/EnemyBullet.h"
#include"../Object/Enemy/GearEnemy/GearEnemy.h"
#include"../Object/Enemy/SpikeEnemy/SpikeEnemy.h"
#include"../Object/Enemy/RushEnemy/RushEnemy.h"
#include"../Object/Enemy/ShotEnemy/ShotEnemy.h"
#include"../Object/Boss/Boss.h"


void C_Collision::Update()
{
	CheckBulletGearEnemy();
	CheckBulletSpikeEnemy();

	CheckPlayerGearEnemy();
	CheckPlayerSpikeEnemy();

	CheckBulletRushEnemy();
	CheckPlayerRushEnemy();

	CheckBulletShotEnemy();
	CheckPlayerShotEnemy();
	CheckPlayerEnemyBullet();

	CheckBulletBoss();
	CheckPlayerBoss();
	CheckBulletSubEnemy();
	CheckPlayerSubEnemy();


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
					m_gearEnemy->Damage(i);
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
					m_spikeEnemy->Damage(i);
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
					m_rushEnemy->Damage(i);
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

void C_Collision::CheckBulletShotEnemy()
{
	for (int i = 0; i < m_shotEnemy->GetNum(); i++)
	{
		for (int j = 0; j < m_bullet->GetNum(); j++)
		{
			if (m_shotEnemy->GetAliveFlg(i) && m_bullet->GetAliveFlg(j))
			{
				Math::Vector2 pos = m_shotEnemy->GetPos(i) - m_bullet->GetPos(j);

				if (pos.Length() < m_bullet->GetRadius() + m_shotEnemy->GetRadius())
				{
					m_shotEnemy->Damage(i);
					m_bullet->SetHitFlg(j, true);
				}
			}
		}
	}
}

void C_Collision::CheckPlayerShotEnemy()
{
	for (int i = 0; i < m_shotEnemy->GetNum(); i++)
	{
		if (m_shotEnemy->GetAliveFlg(i) && m_player->GetAliveFlg())
		{
			Math::Vector2 pos = m_player->GetPos() - m_shotEnemy->GetPos(i);


			if (pos.Length() < m_player->GetRadius() + m_shotEnemy->GetRadius())
			{
				m_shotEnemy->SetHp(0, i);
			}
		}
	}
}

void C_Collision::CheckPlayerEnemyBullet()
{

	for (int i = 0; i < m_enemyBullet->GetNum(); i++)
	{
		if (m_enemyBullet->GetAliveFlg(i) && m_player->GetAliveFlg())
		{
			Math::Vector2 pos = m_player->GetPos() - m_enemyBullet->GetPos(i);

			if (pos.Length() < m_player->GetRadius() + m_enemyBullet->GetRadius())
			{
				m_enemyBullet->SetHitFlg(i, true);
			}
		}
	}

}

void C_Collision::CheckBulletBoss()
{
	for (int i = 0; i < m_bullet->GetNum(); i++)
	{
		if (m_bullet->GetAliveFlg(i) && m_boss->BossGetAliveFlg())
		{
			Math::Vector2 pos = m_bullet->GetPos(i) - m_boss->BossGetPos();

			if (pos.Length() < m_bullet->GetRadius() + m_boss->BossGetRadius())
			{
				m_bullet->SetHitFlg(i,true);
			}
		}
	}
}

void C_Collision::CheckPlayerBoss()
{

	if (m_player->GetAliveFlg() && m_boss->BossGetAliveFlg())
	{
		Math::Vector2 pos = m_player->GetPos() - m_boss->BossGetPos();

		if (pos.Length() < m_player->GetRadius() + m_boss->BossGetRadius())
		{
			
		}
	}


}

void C_Collision::CheckBulletSubEnemy()
{

	// 歯車型の敵との判定
	for (int i = 0; i < m_bullet->GetNum(); i++)
	{
		for (int j = 0; j < m_boss->GEnemyGetNum(); j++)
		{
			if (m_bullet->GetAliveFlg(i) && m_boss->GEnemyGetAliveFlg(j))
			{
				Math::Vector2 pos = m_boss->GEnemyGetPos(j) - m_bullet->GetPos(i);

				if (pos.Length() < m_boss->GEnemyGetRadius() + m_bullet->GetRadius())
				{
					m_bullet->SetHitFlg(i, true);
					m_boss->GEnemyDamage(j);
				}
			}
		}
	}


	// トゲ型の敵との判定
	for (int i = 0; i < m_bullet->GetNum(); i++)
	{
		for (int j = 0; j < m_boss->SEnemyGetNum(); j++)
		{
			if(m_bullet->GetAliveFlg(i)&&m_boss->SEnemyGetAliveFlg(j))
			{
				Math::Vector2 pos = m_boss->SEnemyGetPos(j) - m_bullet->GetPos(i);

				if (pos.Length() < m_boss->SEnemyGetRadius() + m_bullet->GetRadius())
				{
					m_bullet->SetHitFlg(i, true);
					m_boss->SEnemyDamage(j);
				}
			}
		}
	}



}

void C_Collision::CheckPlayerSubEnemy()
{
	// 歯車型の敵との判定
	for (int i = 0; i < m_boss->GEnemyGetNum(); i++)
	{
		if (m_player->GetAliveFlg() && m_boss->GEnemyGetAliveFlg(i))
		{
			Math::Vector2 pos = m_boss->GEnemyGetPos(i) - m_player->GetPos();

			if (pos.Length() < m_player->GetRadius() + m_boss->GEnemyGetRadius())
			{
				m_boss->GEnemySetHp(0, i);
			}
		}
	}



	// トゲ型の敵との判定

	for (int i = 0; i < m_boss->SEnemyGetNum(); i++)
	{
		if (m_player->GetAliveFlg() && m_boss->SEnemyGetAliveFlg(i))
		{
			Math::Vector2 pos = m_boss->SEnemyGetPos(i) - m_player->GetPos();

			if (pos.Length() < m_player->GetRadius() + m_boss->SEnemyGetRadius())
			{
				m_boss->SEnemySetHp(0, i);
			}
		}
	}
}
