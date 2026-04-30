#include "GameUI.h"

#include"../Game/Player.h"

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
	SHADER.m_spriteShader.SetMatrix(s_hpBar_g.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_hpBar_g_Tex, Math::Rectangle(0, 0, 215*m_hpRate, 19), 1.0f);

	//HPアイコン描画
	SHADER.m_spriteShader.SetMatrix(s_hpIcon.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_hpIconTex, Math::Rectangle(0, 0, 258, 30), 1.0f);

	//クールタイムバー描画
	SHADER.m_spriteShader.SetMatrix(s_coolTimeBar.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_coolTimeBarTex, Math::Rectangle(0, 0, 215*m_coolTimeRate, 19), 1.0f);

	//クールタイムアイコン描画
	SHADER.m_spriteShader.SetMatrix(s_coolTimeIcon.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_coolTimeIconTex, Math::Rectangle(0, 0, 258, 30), 1.0f);

	//キャラアイコンの枠描画
	SHADER.m_spriteShader.SetMatrix(s_charaPanel.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_charaPanelTex, Math::Rectangle((int)m_charaPanelAnimCnt * 96, m_player->GetNowElement()*96, 96, 96), 1.0f);


	//キャラアイコンの描画
	SHADER.m_spriteShader.SetMatrix(s_charaIcon.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_charaIconTex, Math::Rectangle(m_player->GetNowElement() *88, 0, 88, 88), 1.0f);
	
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
	s_hpIcon.m_pos = { -380.0f,-290.0f };

	m_hpBar_g_Tex.Load("Textures/UI/hpBar_g_.png");
	s_hpBar_g.m_pos = { -363.0f,-290.0f };
	m_maxWidth = -213;
	m_baseX = -363.0f;

	m_coolTimeIconTex.Load("Textures/UI/coolTimeIcon.png");
	s_coolTimeIcon.m_pos = { -380.0f,-330.0f };

	m_coolTimeBarTex.Load("Textures/UI/coolTimeBar.png");
	s_coolTimeBar.m_pos = { -363.0f,-330.0f };

	m_charaPanelTex.Load("Textures/UI/charaPanel.png");
	s_charaPanel.m_pos = { -560.0f,-300.0f };
	m_charaPanelAnimCnt = 0.0f;

	m_charaIconTex.Load("Textures/UI/charaIcon.png");
	s_charaIcon.m_pos = { -560.0f,-300.0f };

}

void C_GameUI::Update()
{
	//星のアニメーション
	m_starAnimCnt += 0.2;
	if (m_starAnimCnt > 9.0f)
	{
		m_starAnimCnt = 0.0f;
	}

	//キャラパネルのアニメーション
	m_charaPanelAnimCnt += 0.1;
	if (m_charaPanelAnimCnt > 4)
	{
		m_charaPanelAnimCnt = 0.0f;
	}

	// HPバーの割合
	m_hpRate = m_player->GetCurrentHp() / m_player->GetMaxHp();

	// HPバーの座標を管理  初期値   最大幅         最大幅    HPバーの割合  
	s_hpBar_g.m_pos.x = m_baseX + (m_maxWidth - (m_maxWidth * m_hpRate))/2;


	m_coolTimeRate = m_player->GetCurrentCoolTime() / m_player->GetMaxCoolTime();
	s_coolTimeBar.m_pos.x = m_baseX + (m_maxWidth - (m_maxWidth * m_coolTimeRate)) / 2;

	

	s_background.m_mat = Math::Matrix::CreateTranslation(s_background.m_pos.x, s_background.m_pos.y, 0);

	s_hudPanel.m_mat = Math::Matrix::CreateTranslation(s_hudPanel.m_pos.x, s_hudPanel.m_pos.y, 0);

	s_stars.m_mat = Math::Matrix::CreateTranslation(s_stars.m_pos.x, s_stars.m_pos.y, 0);


	s_charaPanel.m_mat = Math::Matrix::CreateTranslation(s_charaPanel.m_pos.x, s_charaPanel.m_pos.y, 0);

	s_charaIcon.m_mat = Math::Matrix::CreateTranslation(s_charaIcon.m_pos.x, s_charaIcon.m_pos.y, 0);

	s_hpIcon.m_mat = Math::Matrix::CreateTranslation(s_hpIcon.m_pos.x, s_hpIcon.m_pos.y, 0);

	s_hpBar_g.m_mat = Math::Matrix::CreateTranslation(s_hpBar_g.m_pos.x, s_hpBar_g.m_pos.y, 0);

	s_coolTimeIcon.m_mat = Math::Matrix::CreateTranslation(s_coolTimeIcon.m_pos.x, s_coolTimeIcon.m_pos.y, 0);
	s_coolTimeBar.m_mat = Math::Matrix::CreateTranslation(s_coolTimeBar.m_pos.x, s_coolTimeBar.m_pos.y, 0);
	
}

void C_GameUI::Release()
{
	m_backgroundTex.Release();
	m_starsTex.Release();
	m_hpIconTex.Release();
	m_charaIconTex.Release();
	m_charaPanelTex.Release();
	m_coolTimeIconTex.Release();
	m_coolTimeBarTex.Release();
	m_hudPanelTex.Release();


}
