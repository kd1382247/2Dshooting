#include "GameScene.h"

#include"../SceneManager.h"
#include"PlayStage.h"

void C_GameScene::Draw()
{
	m_playStage->Draw();
}

void C_GameScene::Update()
{

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		C_SceneManager::GetInstance().SetNextSceneType(C_SceneManager::SceneType::Title);
	}
	m_playStage->Update();
}

void C_GameScene::Init()
{
	m_playStage = std::make_shared<C_PlayStage>();

}
