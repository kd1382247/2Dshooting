#include "GameUI.h"

C_GameUI::C_GameUI()
{
	Init();
}

C_GameUI::~C_GameUI()
{
	Release();
}

void C_GameUI::Draw()
{
	//背景描画
	SHADER.m_spriteShader.SetMatrix(s_background.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_backgroundTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

	//UIパネル描画
	SHADER.m_spriteShader.SetMatrix(s_UiPanel.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_UiPanelTex, Math::Rectangle(0, 0, 299, 98), 0.8f);

	////HPアイコン描画
	//SHADER.m_spriteShader.SetMatrix(s_hpIcon.m_mat);
	//SHADER.m_spriteShader.DrawTex(&m_hpIconTex, Math::Rectangle(0, 0, 150, 20), 1.0f);

	////プレイヤーアイコン描画
	//SHADER.m_spriteShader.SetMatrix(s_playerIcon.m_mat);
	//SHADER.m_spriteShader.DrawTex(&m_playerIconTex, Math::Rectangle(0, 0, 96, 96), 1.0f);


}

void C_GameUI::Init()
{
	m_backgroundTex.Load("background.png");
	s_background.m_pos = {0.0f,0.0f};

	m_hpIconTex.Load("Texture/UI/hpIcon.png");
	s_hpIcon.m_pos = { -300.0f,320.0f };

	m_UiPanelTex.Load("Texture/UI/1111.png");
	s_UiPanel.m_pos = { -480.0f,300.0f };

	m_playerIconTex.Load("Texture/UI/playerIcon.png");
	s_playerIcon.m_pos = { -330.0f,330.0f };

}

void C_GameUI::Update()
{
	s_background.m_mat = Math::Matrix::CreateTranslation(s_background.m_pos.x, s_background.m_pos.y, 0);

	s_UiPanel.m_mat = Math::Matrix::CreateTranslation(s_UiPanel.m_pos.x, s_UiPanel.m_pos.y, 0);

	s_playerIcon.m_mat = Math::Matrix::CreateTranslation(s_playerIcon.m_pos.x, s_playerIcon.m_pos.y, 0);

	s_hpIcon.m_mat = Math::Matrix::CreateTranslation(s_hpIcon.m_pos.x, s_hpIcon.m_pos.y, 0);


}

void C_GameUI::Release()
{
	m_backgroundTex.Release();
}
