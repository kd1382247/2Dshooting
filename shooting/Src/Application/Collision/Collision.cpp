#include "Collision.h"

#include"../Object/Player/Player.h"
#include"../Object/Bullet/Bullet.h"
#include"../Object/Enemy/ShotEnemy/EnemyBullet.h"
#include"../Object/Enemy/GearEnemy/GearEnemy.h"
#include"../Object/Enemy/SpikeEnemy/SpikeEnemy.h"
#include"../Object/Enemy/RushEnemy/RushEnemy.h"
#include"../Object/Enemy/ShotEnemy/ShotEnemy.h"
#include"../Object/Boss/Boss.h"
#include"../Collision/ElementAffinity.h"


void C_Collision::Update()
{

	// 歯車型の敵との判定
	CheckBulletGearEnemy();
	CheckPlayerGearEnemy();

	// トゲ型の敵との判定
	CheckPlayerSpikeEnemy();
	CheckBulletSpikeEnemy();

	// 突進型の敵との判定
	CheckBulletRushEnemy();
	CheckPlayerRushEnemy();

	// 弾発射型の敵との判定
	CheckBulletShotEnemy();
	CheckPlayerShotEnemy();
	CheckPlayerEnemyBullet();

	// ボス、雑魚敵との判定
	CheckBulletBoss();
	CheckPlayerBoss();
	CheckBulletSubEnemy();
	CheckPlayerSubEnemy();

	// シールドとの判定
	CheckBulletShield();
}

void C_Collision::CheckBulletGearEnemy()
{
	for (int e = 0; e < m_gearEnemy->GetNum(); e++)
	{
		for (int bu = 0; bu < m_bullet->GetNum(); bu++)
		{
			if(m_gearEnemy->GetAliveFlg(e)&&m_bullet->GetAliveFlg(bu))
			{
				Math::Vector2 pos = m_gearEnemy->GetPos(e) - m_bullet->GetPos(bu);
				
				if (pos.Length() < m_gearEnemy->GetRadius() + m_bullet->GetRadius())
				{
					m_gearEnemy->Damage(e,m_elementAffinity->CalculateElementDamage(m_bullet->GetElement(bu),m_gearEnemy->GetElement(e),m_bullet->GetAttackPow()));
					m_bullet->SetHitFlg(bu, true);
					m_bullet->SetPopupType(bu, m_elementAffinity->GetPopupType(m_bullet->GetElement(bu), m_gearEnemy->GetElement(e)));
				}
			}
		}
	}
}

void C_Collision::CheckPlayerGearEnemy()
{
	for (int e = 0; e < m_gearEnemy->GetNum(); e++)
	{
		if (m_gearEnemy->GetAliveFlg(e) && m_player->GetAliveFlg())
		{
			Math::Vector2 pos = m_player->GetPos() - m_gearEnemy->GetPos(e);
			

			if (pos.Length() < m_player->GetRadius() + m_gearEnemy->GetRadius())
			{
				if (!m_player->GetHitCoolTimeFlg())
				{
					m_player->Damage(m_elementAffinity->CalculateElementDamage(m_player->GetNowElement(),m_gearEnemy->GetElement(e),m_gearEnemy->GetAttackPow()));
					m_player->SetHitCoolTimeFlg(true);
				}
			}
		}
	}
}

void C_Collision::CheckBulletSpikeEnemy()
{
	for (int e = 0; e < m_spikeEnemy->GetNum(); e++)
	{
		for (int bu = 0; bu < m_bullet->GetNum(); bu++)
		{
			if (m_spikeEnemy->GetAliveFlg(e) && m_bullet->GetAliveFlg(bu))
			{
				Math::Vector2 pos = m_spikeEnemy->GetPos(e) - m_bullet->GetPos(bu);

				if (pos.Length() < m_bullet->GetRadius() + m_spikeEnemy->GetRadius())
				{
					m_spikeEnemy->Damage(e, m_elementAffinity->CalculateElementDamage(m_bullet->GetElement(bu), m_spikeEnemy->GetElement(e), m_bullet->GetAttackPow()));
					m_bullet->SetHitFlg(bu, true);
					m_bullet->SetPopupType(bu, m_elementAffinity->GetPopupType(m_bullet->GetElement(bu), m_spikeEnemy->GetElement(e)));
				}
			}
		}
	}
}

void C_Collision::CheckPlayerSpikeEnemy()
{
	for (int e = 0; e < m_spikeEnemy->GetNum(); e++)
	{
		if (m_spikeEnemy->GetAliveFlg(e) && m_player->GetAliveFlg())
		{
			Math::Vector2 pos = m_player->GetPos() - m_spikeEnemy->GetPos(e);


			if (pos.Length() < m_player->GetRadius() + m_spikeEnemy->GetRadius())
			{
				if (!m_player->GetHitCoolTimeFlg())
				{
					m_player->Damage(m_elementAffinity->CalculateElementDamage(m_player->GetNowElement(), m_spikeEnemy->GetElement(e), m_spikeEnemy->GetAttackPow()));
					m_player->SetHitCoolTimeFlg(true);
				}
			}
		}
	}
}

void C_Collision::CheckBulletRushEnemy()
{
	
	for (int e = 0; e < m_rushEnemy->GetNum(); e++)
	{
		for (int bu = 0; bu < m_bullet->GetNum(); bu++)
		{
			if (m_rushEnemy->GetAliveFlg(e) && m_bullet->GetAliveFlg(bu))
			{
				Math::Vector2 pos = m_rushEnemy->GetPos(e) - m_bullet->GetPos(bu);

				if (pos.Length() < m_bullet->GetRadius() + m_rushEnemy->GetRadius())
				{
					m_rushEnemy->Damage(e, m_elementAffinity->CalculateElementDamage(m_bullet->GetElement(bu), m_rushEnemy->GetElement(e), m_bullet->GetAttackPow()));
					m_bullet->SetHitFlg(bu, true);
					m_bullet->SetPopupType(bu, m_elementAffinity->GetPopupType(m_bullet->GetElement(bu), m_rushEnemy->GetElement(e)));
				}
			}
		}
	}
}

void C_Collision::CheckPlayerRushEnemy()
{
	for (int e = 0; e < m_rushEnemy->GetNum(); e++)
	{
		if (m_rushEnemy->GetAliveFlg(e) && m_player->GetAliveFlg())
		{
			Math::Vector2 pos = m_player->GetPos() - m_rushEnemy->GetPos(e);

			if (pos.Length() < m_player->GetRadius() + m_rushEnemy->GetRadius())
			{
				if (!m_player->GetHitCoolTimeFlg())
				{
					m_player->Damage(m_elementAffinity->CalculateElementDamage(m_player->GetNowElement(), m_rushEnemy->GetElement(e), m_rushEnemy->GetAttackPow()));
					m_player->SetHitCoolTimeFlg(true);
				}
			}
		}
	}
}

void C_Collision::CheckBulletShotEnemy()
{
	for (int e = 0; e < m_shotEnemy->GetNum(); e++)
	{
		for (int bu = 0; bu < m_bullet->GetNum(); bu++)
		{
			if (m_shotEnemy->GetAliveFlg(e) && m_bullet->GetAliveFlg(bu))
			{
				Math::Vector2 pos = m_shotEnemy->GetPos(e) - m_bullet->GetPos(bu);

				if (pos.Length() < m_bullet->GetRadius() + m_shotEnemy->GetRadius())
				{
					m_shotEnemy->Damage(e, m_elementAffinity->CalculateElementDamage(m_bullet->GetElement(bu), m_shotEnemy->GetElement(e), m_bullet->GetAttackPow()));;
					m_bullet->SetHitFlg(bu, true);
					m_bullet->SetPopupType(bu, m_elementAffinity->GetPopupType(m_bullet->GetElement(bu), m_shotEnemy->GetElement(e)));
				}
			}
		}
	}
}

void C_Collision::CheckPlayerShotEnemy()
{
	for (int e = 0; e < m_shotEnemy->GetNum(); e++)
	{
		if (m_shotEnemy->GetAliveFlg(e) && m_player->GetAliveFlg())
		{
			Math::Vector2 pos = m_player->GetPos() - m_shotEnemy->GetPos(e);


			if (pos.Length() < m_player->GetRadius() + m_shotEnemy->GetRadius())
			{
				if (!m_player->GetHitCoolTimeFlg())
				{
					m_player->Damage(m_elementAffinity->CalculateElementDamage(m_player->GetNowElement(), m_shotEnemy->GetElement(e), m_shotEnemy->GetAttackPow()));
					m_player->SetHitCoolTimeFlg(true);
				}
			}
		}
	}
}

void C_Collision::CheckPlayerEnemyBullet()
{

	for (int e = 0; e < m_enemyBullet->GetNum(); e++)
	{
		if (m_enemyBullet->GetAliveFlg(e) && m_player->GetAliveFlg())
		{
			Math::Vector2 pos = m_player->GetPos() - m_enemyBullet->GetPos(e);

			if (pos.Length() < m_player->GetRadius() + m_enemyBullet->GetRadius())
			{
				m_enemyBullet->SetHitFlg(e, true);
				m_player->Damage(m_elementAffinity->CalculateElementDamage(m_player->GetNowElement(), m_enemyBullet->GetElement(e), m_enemyBullet->GetAttackPow()));
			}
		}
	}

}

void C_Collision::CheckBulletBoss()
{
	for (int bu = 0; bu < m_bullet->GetNum(); bu++)
	{
		//															シールドが解除されていたら
		if (m_bullet->GetAliveFlg(bu) && m_boss->BossGetAliveFlg()&&!m_boss->ShieldGetAliveFlg())
		{
			Math::Vector2 pos = m_bullet->GetPos(bu) - m_boss->BossGetPos();

			if (pos.Length() < m_bullet->GetRadius() + m_boss->BossGetRadius())
			{
				m_bullet->SetHitFlg(bu,true);
				m_bullet->SetPopupType(bu, m_elementAffinity->GetPopupType(m_bullet->GetElement(bu), m_boss->BossGetElement()));
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
			if (!m_player->GetHitCoolTimeFlg())
			{
				m_player->Damage(m_elementAffinity->CalculateElementDamage(m_player->GetNowElement(), m_boss->BossGetElement(), m_boss->BossGetAttackPow()));
				m_player->SetHitCoolTimeFlg(true);
			}
		}
	}

}
// 弾とシールド
void C_Collision::CheckBulletShield()
{
	for (int bu = 0; bu < m_bullet->GetNum(); bu++)
	{
		if (m_bullet->GetAliveFlg(bu) && m_boss->ShieldGetAliveFlg())
		{
			Math::Vector2 pos = m_boss->ShieldGetPos() - m_bullet->GetPos(bu);

			if (pos.Length() < m_boss->ShieldGetRadius() + m_bullet->GetRadius())
			{
				m_boss->BossDamage(m_elementAffinity->CalculateElementDamage(m_bullet->GetElement(bu), m_boss->GEnemyGetElement(bu), m_bullet->GetAttackPow()));
				m_bullet->SetHitFlg(bu, true);
				m_bullet->SetShieldHitFlg(bu, true);
			}
		}
	}
}

void C_Collision::CheckBulletSubEnemy()
{

	// 歯車型の敵との判定
	for (int bu = 0; bu < m_bullet->GetNum(); bu++)
	{
		for (int bo = 0; bo < m_boss->GEnemyGetNum(); bo++)
		{
			if (m_bullet->GetAliveFlg(bu) && m_boss->GEnemyGetAliveFlg(bo))
			{
				Math::Vector2 pos = m_boss->GEnemyGetPos(bo) - m_bullet->GetPos(bu);

				if (pos.Length() < m_boss->GEnemyGetRadius() + m_bullet->GetRadius())
				{
					m_boss->GEnemyDamage(bo, m_elementAffinity->CalculateElementDamage(m_bullet->GetElement(bu), m_boss->GEnemyGetElement(bo), m_bullet->GetAttackPow()));
					m_bullet->SetHitFlg(bu, true);
					m_bullet->SetPopupType(bu, m_elementAffinity->GetPopupType(m_bullet->GetElement(bu), m_boss->GEnemyGetElement(bo)));
				}
			}
		}
	}

	// トゲ型の敵との判定
	for (int bu = 0; bu < m_bullet->GetNum(); bu++)
	{
		for (int bo = 0; bo < m_boss->SEnemyGetNum(); bo++)
		{
			if (m_bullet->GetAliveFlg(bu) && m_boss->SEnemyGetAliveFlg(bo))
			{
				Math::Vector2 pos = m_boss->SEnemyGetPos(bo) - m_bullet->GetPos(bu);

				if (pos.Length() < m_boss->SEnemyGetRadius() + m_bullet->GetRadius())
				{
					m_boss->SEnemyDamage(bo, m_elementAffinity->CalculateElementDamage(m_bullet->GetElement(bu), m_boss->SEnemyGetElement(bo), m_bullet->GetAttackPow()));
					m_bullet->SetHitFlg(bu, true);
					m_bullet->SetPopupType(bu, m_elementAffinity->GetPopupType(m_bullet->GetElement(bu), m_boss->SEnemyGetElement(bo)));
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
				if (!m_player->GetHitCoolTimeFlg())
				{
					m_player->Damage(m_elementAffinity->CalculateElementDamage(m_player->GetNowElement(), m_boss->GEnemyGetElement(i), m_boss->GEnemyGetAttackPow()));
					m_player->SetHitCoolTimeFlg(true);
				}
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
				if(!m_player->GetHitCoolTimeFlg())
				{
					m_player->Damage(m_elementAffinity->CalculateElementDamage(m_player->GetNowElement(), m_boss->SEnemyGetElement(i), m_boss->SEnemyGetAttackPow()));
					m_player->SetHitCoolTimeFlg(true);
				}
				if(m_boss->SEnemyGetHomingFlg(i))
				{
					m_boss->SEnemySetHomingFlg(i, false);
				}
			}
		}
	}
}