#include "Title.h"

void C_Title::Draw()
{

	//タイトル描画
	SHADER.m_spriteShader.SetMatrix(s_title.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_titleTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

	//プレスエンター描画
	SHADER.m_spriteShader.SetMatrix(s_pressEnter.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_pressEnterTex, Math::Rectangle(0, 0, 377, 35), m_alpha);
}

void C_Title::Update()
{

	m_alpha += m_delta;
	if (m_alpha > 1.0f)
	{
		m_delta *= -1;
	}
	else if (m_alpha < 0.0f)
	{
		m_delta *= -1;
	}


	s_title.m_mat = Math::Matrix::CreateTranslation(s_title.m_pos.x, s_title.m_pos.y, 0);
	s_pressEnter.m_mat = Math::Matrix::CreateTranslation(s_pressEnter.m_pos.x, s_pressEnter.m_pos.y, 0);
	
}

void C_Title::Init()
{
	m_titleTex.Load("Textures/UI/title.png");
	s_title.m_pos = { 0.0f,0.0f };

	m_pressEnterTex.Load("Textures/UI/pressEnter.png");
	s_pressEnter.m_pos = { 0.0f,-190.0f };

	m_alpha = 1.0f;
	m_delta = 0.01;
}

void C_Title::Release()
{
	m_titleTex.Release();
	m_pressEnterTex.Release();
}
