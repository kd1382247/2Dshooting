#include "GameScene.h"

#include"../SceneManager.h"
#include"../Game/Player.h"
#include"../Game/Bullet.h"
#include"../UI/GameUI.h"
#include"../Game/Enemy.h"


void C_GameScene::Draw()
{
	m_gameUi->Draw();
	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Draw();
	}
}

void C_GameScene::Update()
{

	
	m_gameUi->Update();

	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Update();
	}
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		C_SceneManager::GetInstance().SetNextSceneType(C_SceneManager::SceneType::Title);
	}
	
}

void C_GameScene::Init()
{
	m_gameUi = std::make_shared<C_GameUI>();

	std::shared_ptr<C_Player>player;
	player = std::make_shared<C_Player>();
	m_objList.push_back(player);

	std::shared_ptr<C_Bullet>bullet;
	bullet = std::make_shared<C_Bullet>();
	m_objList.push_back(bullet);

	std::shared_ptr<C_Enemy>enemy;
	enemy = std::make_shared<C_Enemy>();
	m_objList.push_back(enemy);


	//インスタンス生成後にインスタンスを渡す
	player->SetInstance(bullet);
	bullet->SetInstance(player);
	m_gameUi->SetInstance(player);
	
}
