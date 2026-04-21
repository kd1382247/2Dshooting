#include "PlayStage.h"

C_PlayStage::C_PlayStage()
{

}

C_PlayStage::~C_PlayStage()
{
	Release();
}

void C_PlayStage::Draw()
{

	m_ui.Draw();
	m_player.Draw();
}

void C_PlayStage::Update()
{

	m_ui.Update();
	m_player.Update();
}

void C_PlayStage::Init()
{
	
}

void C_PlayStage::Release()
{

}
