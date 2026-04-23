#include "PlayStage.h"
#include"../GameScene/Player/Player.h"
#include"../GameScene/GameUI.h"

C_PlayStage::C_PlayStage()
{

}

C_PlayStage::~C_PlayStage()
{
	Release();
}

void C_PlayStage::Draw()
{

	m_gameUi->Draw();
	m_player->Draw();
}

void C_PlayStage::Update()
{

	m_gameUi->Update();
	m_player->Update();
}

void C_PlayStage::Init()
{

	m_player = new C_Player();
	m_gameUi = new C_GameUI();
}

void C_PlayStage::Release()
{
	if (m_player)
	{
		delete m_player;
		m_player = nullptr;
	}

	if (m_gameUi)
	{
		delete m_gameUi;
		m_gameUi = nullptr;
	}
}
