#pragma once

class C_Player;
class C_Bullet;
class C_EnemyBullet;
class C_GearEnemy;
class C_SpikeEnemy;
class C_RushEnemy;
class C_ShotEnemy;

class C_Collision
{
public:

	C_Collision(){}
	~C_Collision(){}

	void Update();

	void SetInstance(std::shared_ptr<C_Player>a_player,
		             std::shared_ptr<C_Bullet>a_bulle,
		             std::shared_ptr<C_EnemyBullet>a_enemyBulle,
		             std::shared_ptr<C_GearEnemy>a_gearEnemy,
		             std::shared_ptr<C_SpikeEnemy>a_spikeEnemy,
		             std::shared_ptr<C_RushEnemy>a_rushEnemy,
					 std::shared_ptr<C_ShotEnemy>a_shotEnemy)
	{
		m_player = a_player;
		m_bullet = a_bulle;
		m_enemyBullet = a_enemyBulle;
		m_gearEnemy = a_gearEnemy;
		m_spikeEnemy = a_spikeEnemy;
		m_rushEnemy = a_rushEnemy;
		m_shotEnemy = a_shotEnemy;
	}
	

private:

	// 歯車型の敵との判定
	void CheckBulletGearEnemy();
	void CheckPlayerGearEnemy();

	// トゲ型の敵との判定
	void CheckBulletSpikeEnemy();
	void CheckPlayerSpikeEnemy();

	// 突撃タイプの敵との判定
	void CheckBulletRushEnemy();
	void CheckPlayerRushEnemy();

	// 弾を撃つタイプの敵との判定
	void CheckBulletShotEnemy();
	void CheckPlayerShotEnemy();
	void CheckPlayerEnemyBullet();



	std::shared_ptr<C_Player>m_player=nullptr;
	std::shared_ptr<C_Bullet>m_bullet=nullptr;
	std::shared_ptr<C_EnemyBullet>m_enemyBullet=nullptr;
	std::shared_ptr<C_GearEnemy>m_gearEnemy=nullptr;
	std::shared_ptr<C_SpikeEnemy>m_spikeEnemy = nullptr;
	std::shared_ptr<C_RushEnemy>m_rushEnemy = nullptr;
	std::shared_ptr<C_ShotEnemy>m_shotEnemy = nullptr;

};