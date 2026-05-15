#include "GameController.h"


#include"../../../Object/Enemy/GearEnemy/GearEnemy.h"
#include"../../../Object/Enemy/SpikeEnemy/SpikeEnemy.h"
#include"../../../Object/Enemy/RushEnemy/RushEnemy.h"
#include"../../../Object/Enemy/ShotEnemy/ShotEnemy.h"
#include"../../../Object/Boss/Boss.h"


void C_GameController::SpawnEnemies()
{

	m_gameCnt++;

	if (m_spawnPatternCnt == 0)
	{
		if (!m_spawnFlg)
		{
			m_gearEnemy->Spawn();
			m_spawnFlg = true;
		}
		if (m_gameCnt > 60 * 15 || m_gearEnemy->GetAliveFalseFlg())
		{
			m_spawnPatternCnt = 1;
			m_spawnFlg = false;
		}
	}
	if (m_spawnPatternCnt == 1)
	{

		if (!m_spawnFlg)
		{
			m_spikeEnemy->Spawn();
			m_spawnFlg = true;
		}

		if (m_gameCnt > 60 * 30 || m_spikeEnemy->GetAliveFalseFlg())
		{
			m_spawnPatternCnt = 2;
			m_spawnFlg = false;
		}
	}
	if (m_spawnPatternCnt == 2)
	{
		if (!m_spawnFlg)
		{
			m_rushEnemy->Spawn();
			m_spawnFlg = true;
		}
		if (m_gameCnt > 60 * 65 || m_rushEnemy->GetAliveFalseFlg())
		{
			m_spawnPatternCnt = 3;
			m_spawnFlg = false;
		}
	}

	if (m_spawnPatternCnt == 3)
	{
		if (!m_spawnFlg)
		{
			m_shotEnemy->Spawn();
			m_spawnFlg = true;
		}
		if (m_shotEnemy->GetAliveFalseFlg())
		{
			m_spawnPatternCnt = 4;
			m_spawnFlg = false;
		}
	}

	if (m_spawnPatternCnt == 4)
	{
		if (!m_spawnFlg)
		{
			m_boss->SpawnBoss();
			m_spawnFlg = true;
		}
	}

}
