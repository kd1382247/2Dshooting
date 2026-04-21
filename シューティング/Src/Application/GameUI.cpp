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
	SHADER.m_spriteShader.SetMatrix(s_background.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_backgroundTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);
}

void C_GameUI::Init()
{
	m_backgroundTex.Load("background.png");
	s_background.m_pos = {0,0};
}

void C_GameUI::Update()
{
	s_background.m_mat = Math::Matrix::CreateTranslation(s_background.m_pos.x, s_background.m_pos.y, 0);
}

void C_GameUI::Release()
{
	m_backgroundTex.Release();
}
