#include "GameScene.h"

#include"../../SceneManager.h"

#include"../../Object/Player/Player.h"
#include"../../Object/Bullet/Bullet.h"
#include"../../Object/Enemy/ShotEnemy/EnemyBullet.h"
#include"../../UI/GameUI.h"
#include"../../Collision/Collision.h"
#include"GameController/GameController.h"
#include"../../UI/Score/Score.h"
#include"../../UI/Result/Result.h"
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


	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Draw();
	}
	m_gameUi->Draw();

	m_score->Draw();

	m_result->Draw();

}

void C_GameScene::Update()
{


	if (!m_result->GetResultFlg())
	{
		m_gameCtr->SpawnEnemies();

		for (int i = 0; i < m_objList.size(); i++)
		{
			m_objList[i]->Update();
		}
		
		m_collision->Update();
		m_score->Update();
		
	}

	if (m_result->GetResultFlg())
	{
		// リスタート
		if (GetAsyncKeyState('R') & 0x8000)
		{
			C_SceneManager::GetInstance().SetNextSceneType(C_SceneManager::SceneType::Restart);
		}
		// タイトル
		if (GetAsyncKeyState('T') & 0x8000)
		{
			C_SceneManager::GetInstance().SetNextSceneType(C_SceneManager::SceneType::Title);
		}
		
	}
	
	m_gameUi->Update();
	m_result->Update();
}

void C_GameScene::Init()
{
	// ゲーム画面のUI
	m_gameUi = std::make_shared<C_GameUI>();

	// 当たり判定
	m_collision = std::make_shared<C_Collision>();

	// ゲームコントローラー
	m_gameCtr = std::make_shared<C_GameController>();

	// スコア
	m_score = std::make_shared<C_Score>();
	
	// リザルト
	m_result = std::make_shared<C_Result>();

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

	// 敵の弾
	std::shared_ptr<C_EnemyBullet>enemyBullet;
	enemyBullet = std::make_shared<C_EnemyBullet>();
	m_objList.push_back(enemyBullet);

	// ボス
	std::shared_ptr<C_Boss>boss;
	boss = std::make_shared<C_Boss>();
	m_objList.push_back(boss);

	// プレイヤー
	std::shared_ptr<C_Player>player;
	player = std::make_shared<C_Player>();
	m_objList.push_back(player);

	// プレイヤーの弾
	std::shared_ptr<C_Bullet>bullet;
	bullet = std::make_shared<C_Bullet>();
	m_objList.push_back(bullet);


	//インスタンス生成後にインスタンスを渡す
	m_gameUi->  SetInstance(player,boss);
	m_score->SetInstance(m_result);
	player->    SetInstance(bullet,m_result);
	gearEnemy-> SetInstance(m_score,player);
	spikeEnemy->SetInstance(m_score,player);
	rushEnemy-> SetInstance(m_score,player);
	shotEnemy-> SetInstance(enemyBullet,m_score,player);
	boss->      SetInstance(player,m_result,m_score);
	
	

	m_gameCtr->SetInstance(gearEnemy,
						   spikeEnemy,
						   rushEnemy,
		                   shotEnemy,
		                   boss);

	m_collision->SetInstance(player,
		                     bullet,
		                     enemyBullet,
		                     gearEnemy,
		                     spikeEnemy,
		                     rushEnemy,
							 shotEnemy,
							 boss);


}
