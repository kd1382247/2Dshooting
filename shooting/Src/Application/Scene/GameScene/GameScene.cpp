#include "GameScene.h"
#include"PlayStage.h"

void C_GameScene::Draw()
{
	m_playStage->Draw();
}

void C_GameScene::Update()
{
	m_playStage->Update();
}

void C_GameScene::Init()
{
	m_playStage = std::make_shared<C_PlayStage>();

}
