#include "GameUI.h"

#include"../Object/Player/Player.h"

void C_GameUI::Draw()
{

	//背景描画
	SHADER.m_spriteShader.SetMatrix(s_background.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_backgroundTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);


	//星描画
	SHADER.m_spriteShader.SetMatrix(s_stars.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_starsTex, Math::Rectangle((int)m_starAnimCnt * 1280, 0, 1280, 720), 1.0f);


	//HUD描画
	SHADER.m_spriteShader.SetMatrix(s_hudPanel.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_hudPanelTex, Math::Rectangle(0, 0, 1280, 120), 1.0f);

	//HPバー(緑)描画
	SHADER.m_spriteShader.SetMatrix(s_hpBar.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_hpBarTex, Math::Rectangle(0, 0, 215*m_hpRate, 19), 1.0f);

	//HPアイコン描画
	SHADER.m_spriteShader.SetMatrix(s_hpIcon.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_hpIconTex, Math::Rectangle(0, 0, 258, 30), 1.0f);

	//クールタイムバー描画
	SHADER.m_spriteShader.SetMatrix(s_coolTimeBar.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_coolTimeBarTex, Math::Rectangle(0, 0, 215*m_coolTimeRate, 19), 1.0f);

	//クールタイムアイコン描画
	SHADER.m_spriteShader.SetMatrix(s_coolTimeIcon.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_coolTimeIconTex, Math::Rectangle(0, 0, 258, 30), 1.0f);


	// 炎アイコン描画
	SHADER.m_spriteShader.SetMatrix(s_fireIcon.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_fireIconTex, Math::Rectangle(0, 0, 64, 100), m_fireAlpha);

	// 草アイコン描画
	SHADER.m_spriteShader.SetMatrix(s_grassIcon.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_grassIconTex, Math::Rectangle(0, 0, 64, 100), m_grassAlpha);

	// 水アイコン描画
	SHADER.m_spriteShader.SetMatrix(s_waterIcon.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_waterIconTex, Math::Rectangle(0, 0, 64, 100), m_waterAlpha);
}

void C_GameUI::Init()
{
	m_backgroundTex.Load("Textures/UI/background.png");
	s_background.m_pos = {0.0f,0.0f};

	m_hudPanelTex.Load("Textures/UI/hudPanel.png");
	s_hudPanel.m_pos = { 0.0f,-300.0f };

	m_starsTex.Load("Textures/UI/stars.png");
	s_stars.m_pos = { 0.0f,0.0f };
	m_starAnimCnt = 0.0f;

	m_hpIconTex.Load("Textures/UI/hpIcon.png");
	s_hpIcon.m_pos = { -260.0f,-300.0f };

	m_hpBarTex.Load("Textures/UI/hpBar_g_.png");
	s_hpBar.m_pos = { -243.0f,-300.0f };
	m_maxWidth = -213;
	m_baseX = -243.0f;

	m_coolTimeIconTex.Load("Textures/UI/coolTimeIcon.png");
	s_coolTimeIcon.m_pos = { -260.0f ,-335.0f };

	m_coolTimeBarTex.Load("Textures/UI/coolTimeBar.png");
	s_coolTimeBar.m_pos = { -243.0f,-335.0f };


	m_fireIconTex.Load("Textures/UI/fireIcon.png");
	s_fireIcon.m_pos= { -580 ,-300 };
	m_fireAlpha = 1.0f;

	m_grassIconTex.Load("Textures/UI/grassIcon.png");
	s_grassIcon.m_pos = { -510,-300 };
	m_grassAlpha = 1.0f;

	m_waterIconTex.Load("Textures/UI/waterIcon.png");
	s_waterIcon.m_pos = { -440,-300 };
	m_waterAlpha = 1.0f;

}

void C_GameUI::Update()
{
	
	if (m_player->GetNowElement() == C_Player::Fire)
	{
		m_fireAlpha = 1.0f;
		m_waterAlpha = 0.5;
		m_grassAlpha = 0.5;
	}
	if (m_player->GetNowElement() == C_Player::Grass)
	{
		m_fireAlpha = 0.5f;
		m_waterAlpha = 0.5;
		m_grassAlpha = 1.0;
	}
	if (m_player->GetNowElement() == C_Player::Water)
	{
		m_fireAlpha = 0.5f;
		m_waterAlpha = 1.0;
		m_grassAlpha = 0.5;
	}
	

	// 炎アイコン
	s_fireIcon.m_mat = Math::Matrix::CreateTranslation(s_fireIcon.m_pos.x, s_fireIcon.m_pos.y, 0);

	// 草アイコン
	s_grassIcon.m_mat = Math::Matrix::CreateTranslation(s_grassIcon.m_pos.x, s_grassIcon.m_pos.y, 0);

	// 水アイコン
	s_waterIcon.m_mat = Math::Matrix::CreateTranslation(s_waterIcon.m_pos.x, s_waterIcon.m_pos.y, 0);

	


	// 背景
	s_background.m_mat = Math::Matrix::CreateTranslation(s_background.m_pos.x, s_background.m_pos.y, 0);

	// HUD
	s_hudPanel.m_mat = Math::Matrix::CreateTranslation(s_hudPanel.m_pos.x, s_hudPanel.m_pos.y, 0);



	//星のアニメーション
	m_starAnimCnt += 0.2;
	if (m_starAnimCnt > 9.0f)
	{
		m_starAnimCnt = 0.0f;
	}

	// 星
	s_stars.m_mat = Math::Matrix::CreateTranslation(s_stars.m_pos.x, s_stars.m_pos.y, 0);



	// HPバーの割合
	m_hpRate = m_player->GetCurrentHp() / m_player->GetMaxHp();
	//                   初期値   最大幅         最大幅     バーの割合  
	s_hpBar.m_pos.x = m_baseX + (m_maxWidth - (m_maxWidth * m_hpRate)) / 2;

	// HPアイコン
	s_hpIcon.m_mat = Math::Matrix::CreateTranslation(s_hpIcon.m_pos.x, s_hpIcon.m_pos.y, 0);
	//　HPバー
	s_hpBar.m_mat = Math::Matrix::CreateTranslation(s_hpBar.m_pos.x, s_hpBar.m_pos.y, 0);



	// クールタイムバーの割合
	m_coolTimeRate = m_player->GetCurrentCoolTime() / m_player->GetMaxCoolTime();
	//                         初期値   最大幅         最大幅      バーの割合
	s_coolTimeBar.m_pos.x = m_baseX + (m_maxWidth - (m_maxWidth * m_coolTimeRate)) / 2;

	// クールタイムアイコン
	s_coolTimeIcon.m_mat = Math::Matrix::CreateTranslation(s_coolTimeIcon.m_pos.x, s_coolTimeIcon.m_pos.y, 0);
	// クールタイムバー
	s_coolTimeBar.m_mat = Math::Matrix::CreateTranslation(s_coolTimeBar.m_pos.x, s_coolTimeBar.m_pos.y, 0);
	
}

void C_GameUI::Release()
{
	m_backgroundTex.Release();
	m_starsTex.Release();
	m_hpIconTex.Release();
	m_coolTimeIconTex.Release();
	m_coolTimeBarTex.Release();
	m_hudPanelTex.Release();
	m_fireIconTex.Release();
	m_waterIconTex.Release();
	m_grassIconTex.Release();
}
