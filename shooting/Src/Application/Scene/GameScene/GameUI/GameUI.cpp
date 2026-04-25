#include "GameUI.h"

void C_GameUI::Draw()
{

	//背景描画
	SHADER.m_spriteShader.SetMatrix(s_background.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_backgroundTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);


	//星描画
	SHADER.m_spriteShader.SetMatrix(s_stars.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_starsTex, Math::Rectangle((int)m_animCnt * 1280, 0, 1280, 720), 1.0f);


	//HUD描画
	SHADER.m_spriteShader.SetMatrix(s_hud.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_hudTex, Math::Rectangle(0, 0, 1280, 120), 1.0f);


	//UIパネル描画
	/*SHADER.m_spriteShader.SetMatrix(s_UiPanel.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_UiPanelTex, Math::Rectangle(0, 0, 299, 98), 0.8f);*/

	////HPアイコン描画
	//SHADER.m_spriteShader.SetMatrix(s_hpIcon.m_mat);
	//SHADER.m_spriteShader.DrawTex(&m_hpIconTex, Math::Rectangle(0, 0, 150, 20), 1.0f);

	////プレイヤーアイコン描画
	//SHADER.m_spriteShader.SetMatrix(s_playerIcon.m_mat);
	//SHADER.m_spriteShader.DrawTex(&m_playerIconTex, Math::Rectangle(0, 0, 96, 96), 1.0f);

	
}

void C_GameUI::Init()
{

	m_backgroundTex.Load("Textures/UI/background.png");
	s_background.m_pos = {0.0f,0.0f};

	m_hudTex.Load("Textures/UI/hud.png");
	s_hud.m_pos = { 0.0f,-300.0f };

	m_starsTex.Load("Textures/UI/stars.png");
	s_stars.m_pos = { 0.0f,0.0f };
	m_animCnt = 0.0f;

	m_hpIconTex.Load("Textures/UI/hpIcon.png");
	s_hpIcon.m_pos = { -300.0f,320.0f };

	m_UiPanelTex.Load("Textures/UI/1111.png");
	s_UiPanel.m_pos = { -480.0f,-300.0f };

	m_playerIconTex.Load("Textures/UI/playerIcon.png");
	s_playerIcon.m_pos = { -330.0f,-330.0f };

}

void C_GameUI::Update()
{

	m_animCnt += 0.2;
	if (m_animCnt > 9.0f)
	{
		m_animCnt = 0.0f;
	}

	
	s_background.m_mat = Math::Matrix::CreateTranslation(s_background.m_pos.x, s_background.m_pos.y, 0);

	s_hud.m_mat = Math::Matrix::CreateTranslation(s_hud.m_pos.x, s_hud.m_pos.y, 0);

	s_stars.m_mat = Math::Matrix::CreateTranslation(s_stars.m_pos.x, s_stars.m_pos.y, 0);

	s_UiPanel.m_mat = Math::Matrix::CreateTranslation(s_UiPanel.m_pos.x, s_UiPanel.m_pos.y, 0);

	s_playerIcon.m_mat = Math::Matrix::CreateTranslation(s_playerIcon.m_pos.x, s_playerIcon.m_pos.y, 0);

	s_hpIcon.m_mat = Math::Matrix::CreateTranslation(s_hpIcon.m_pos.x, s_hpIcon.m_pos.y, 0);

}

void C_GameUI::Release()
{
	m_backgroundTex.Release();
	m_hpIconTex.Release();
	m_UiPanelTex.Release();
	m_playerIconTex.Release();

}
