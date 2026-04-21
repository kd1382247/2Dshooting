#include "GameUI.h"

C_GameUI::C_GameUI()
{
	Init();
}

C_GameUI::~C_GameUI()
{
	//Release();
}

void C_GameUI::Draw()
{
	//背景描画
	SHADER.m_spriteShader.SetMatrix(s_background.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_backgroundTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

	//HPアイコン描画
	SHADER.m_spriteShader.SetMatrix(s_hpIcon.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_hpIconTex, Math::Rectangle(0, 0, 200, 58), 1.0f);
}

void C_GameUI::Init()
{
	m_backgroundTex.Load("background.png");
	s_background.m_pos = {0,0};

	m_hpIconTex.Load("Texture/UI/hpIcon.png");
	s_hpIcon.m_pos = { 300,-200 };

}

void C_GameUI::Update()
{
	s_background.m_mat = Math::Matrix::CreateTranslation(s_background.m_pos.x, s_background.m_pos.y, 0);
	s_hpIcon.m_mat = Math::Matrix::CreateTranslation(s_hpIcon.m_pos.x, s_hpIcon.m_pos.y, 0);
}

void C_GameUI::Release()
{
	m_backgroundTex.Release();
}
