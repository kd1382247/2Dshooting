#include "PlayStage.h"
#include"../GameScene/Player/Player.h"
#include"../GameScene/GameUI/GameUI.h"

void C_PlayStage::Draw()
{
	m_gameUi->Draw(m_player->GetNowElement());
	m_player->Draw();
}

void C_PlayStage::Update()
{


	m_player->Update();
	m_gameUi->Update(m_player->GetCurrentHp(),      m_player->GetMaxHp(),
		             m_player->GetCurrentCoolTime(),m_player->GetMaxCoolTime());
	
	
}

void C_PlayStage::Init()
{
	m_player = std::make_shared<C_Player>();
	m_gameUi = std::make_shared<C_GameUI>();
}

void C_PlayStage::Release()
{
	
}
