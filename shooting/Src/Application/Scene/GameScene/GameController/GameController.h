#pragma once

class C_GearEnemy;
class C_SpikeEnemy;
class C_RushEnemy;
class C_ShotEnemy;
class C_Boss;


class C_GameController
{
public:

	C_GameController() {}
	~C_GameController(){}

	void SetInstance(
		std::shared_ptr<C_GearEnemy>a_gearEnemy,
		std::shared_ptr<C_SpikeEnemy>a_spikeEnemy,
		std::shared_ptr<C_RushEnemy>a_rushEnemy,
		std::shared_ptr<C_ShotEnemy>a_shotEnemy,
		std::shared_ptr<C_Boss>a_boss)
	{
		m_gearEnemy = a_gearEnemy;
		m_spikeEnemy = a_spikeEnemy;
		m_rushEnemy = a_rushEnemy;
		m_shotEnemy = a_shotEnemy;
		m_boss = a_boss;
	}

	
	void SpawnEnemies();


private:
	
	float m_gameCnt = {};
	float m_spawnPatternCnt = 0;
	bool  m_spawnFlg = false;

	

	static const int cnt=4;

	std::shared_ptr<C_GearEnemy>      m_gearEnemy = nullptr;
	std::shared_ptr<C_SpikeEnemy>     m_spikeEnemy = nullptr;
	std::shared_ptr<C_RushEnemy>      m_rushEnemy = nullptr;
	std::shared_ptr<C_ShotEnemy>      m_shotEnemy = nullptr;
	std::shared_ptr<C_Boss>           m_boss = nullptr;
};
