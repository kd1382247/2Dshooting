#include "GameScene.h"

#include"../../SceneManager.h"

#include"../../Object/Player/Player.h"
#include"../../Object/Bullet/Bullet.h"
#include"../../Object/Enemy/ShotEnemy/EnemyBullet.h"
#include"../../UI/GameUI.h"
#include"../../Collision/Collision.h"
// 敵
#include"../../Object/Enemy//GearEnemy/GearEnemy.h"
#include"../../Object/Enemy/SpikeEnemy/SpikeEnemy.h"
#include"../../Object/Enemy/RushEnemy/RushEnemy.h"
#include"../../Object/Enemy/ShotEnemy/ShotEnemy.h"
// ボス
#include"../../Object/Boss/Boss.h"

void C_GameScene::Draw()
{
	m_gameUi->Draw2();


	m_boss->Draw();

	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Draw();
	}

	

	m_gameUi->Draw();
}

void C_GameScene::Update()
{

	m_gameUi->Update();

	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Update();
	}
	
	m_boss->Update();

	m_collision->Update();

	if (GetAsyncKeyState('7') & 0x8000)
	{
		C_SceneManager::GetInstance().SetNextSceneType(C_SceneManager::SceneType::Title);
	}
	
}

void C_GameScene::Init()
{
	m_gameUi = std::make_shared<C_GameUI>();


	m_collision = std::make_shared<C_Collision>();

	m_boss = std::make_shared<C_Boss>();


	
	std::shared_ptr<C_Player>player;
	player = std::make_shared<C_Player>();
	m_objList.push_back(player);

	// 歯車型の敵
	std::shared_ptr<C_GearEnemy>gearEnemy;
	gearEnemy = std::make_shared<C_GearEnemy>();
	m_objList.push_back(gearEnemy);

	// トゲ型の敵
	std::shared_ptr<C_SpikeEnemy>spikeEnemy;
	spikeEnemy = std::make_shared<C_SpikeEnemy>();
	m_objList.push_back(spikeEnemy);

	// 突進タイプの敵
	std::shared_ptr<C_RushEnemy>rushEnemy;
	rushEnemy = std::make_shared<C_RushEnemy>();
	m_objList.push_back(rushEnemy);

	// 弾を撃ってくるタイプの敵
	std::shared_ptr<C_ShotEnemy>shotEnemy;
	shotEnemy = std::make_shared<C_ShotEnemy>();
	m_objList.push_back(shotEnemy);

	// プレイヤーの弾
	std::shared_ptr<C_Bullet>bullet;
	bullet = std::make_shared<C_Bullet>();
	m_objList.push_back(bullet);

	// 敵の弾
	std::shared_ptr<C_EnemyBullet>enemyBullet;
	enemyBullet = std::make_shared<C_EnemyBullet>();
	m_objList.push_back(enemyBullet);


	//インスタンス生成後にインスタンスを渡す
	m_gameUi->SetInstance(player);
	player->SetInstance(bullet);
	shotEnemy->SetInstance(enemyBullet);
	m_boss->SetInstance(player);

	m_collision->SetInstance(player,
		                     bullet,
		                     enemyBullet,
		                     gearEnemy,
		                     spikeEnemy,
		                     rushEnemy,
							 shotEnemy,
							 m_boss);


}
