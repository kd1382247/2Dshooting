#include "Result.h"

void C_Result::Draw()
{

	if (!m_resultFlg && m_gameClearFlg)
	{
		// クリア画像
		SHADER.m_spriteShader.SetMatrix(s_clear.m_mat);
		SHADER.m_spriteShader.DrawTex(&m_clearTex, Math::Rectangle(0, 0, 497, 99), 1.0f);
	}

	if (!m_resultFlg && m_gameOverFlg)
	{
		// ゲームオーバー画像
		SHADER.m_spriteShader.SetMatrix(s_gameOver.m_mat);
		SHADER.m_spriteShader.DrawTex(&m_gameOverTex, Math::Rectangle(0, 0, 449, 99), 1.0f);
	}


	if (!m_resultFlg)return;

	
	// 背景(黒画像)
	SHADER.m_spriteShader.SetMatrix(s_background.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_backgroundTex, Math::Rectangle(0, 0, 1280, 720), 0.8f);

	// UIパネル
	SHADER.m_spriteShader.SetMatrix(s_uiPanel.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_uiPanelTex, Math::Rectangle(0,0,812,500), 1.0f);

	// タイトルバー
	SHADER.m_spriteShader.SetMatrix(s_titleBar.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_titleBarTex, Math::Rectangle(), 1.0f);

	// リスタートバー
	SHADER.m_spriteShader.SetMatrix(s_restartBar.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_restartBarTex, Math::Rectangle(), 1.0f);


}

void C_Result::Update()
{

	GameClear();
	GameOver();

	if (!m_resultFlg)return;

	// タイトルバー
	s_titleBar.m_mat = Math::Matrix::CreateTranslation(s_titleBar.m_pos.x, s_titleBar.m_pos.y, 0);

	// リスタートバー
	s_restartBar.m_mat = Math::Matrix::CreateTranslation(s_restartBar.m_pos.x, s_restartBar.m_pos.y, 0);


	// 背景(黒画像)
	s_background.m_mat = Math::Matrix::CreateTranslation(s_background.m_pos.x, s_background.m_pos.y, 0);

	// UIパネル
	s_uiPanel.m_mat = Math::Matrix::CreateTranslation(s_uiPanel.m_pos.x, s_uiPanel.m_pos.y, 0);
}

void C_Result::Init()
{
	m_backgroundTex.Load("Textures/Result/background.png");
	s_background.m_pos = {0,0};

	m_uiPanelTex.Load("Textures/Result/resultPanel.png");
	s_uiPanel.m_pos = { 0,50 };

	m_clearTex.Load("Textures/Result/gameClear.png");
	s_clear.m_pos = { 0,100 };

	m_gameOverTex.Load("Textures/Result/gameOver.png");
	s_gameOver.m_pos = { 0,120 };

	m_titleBarTex.Load("Textures/Result/");

	m_restartBarTex.Load("Textures/Result/");

}

void C_Result::Release()
{
	m_backgroundTex.Release();
	m_uiPanelTex.Release();
	m_clearTex.Release();
	m_gameOverTex.Release();
	m_titleBarTex.Release();
	m_restartBarTex.Release();

}

void C_Result::GameClear()
{
	if (m_gameClearFlg)
	{

		if (!m_scaleUpDownFlg)
		{
			m_clearScale += 0.01;
			if (m_clearScale >= 1.0f)
			{
				m_scaleUpDownFlg = true;
				m_clearScale = 1.0f;
			}
		}
		else
		{
			m_clearScale -= 0.01;
			if (m_clearScale < 0.6f)
			{
				m_clearScale = 0.6f;
				m_scaleUpDownFlg = false;
			}
		}
		m_scaleUpDownCnt++;

		if (m_scaleUpDownCnt > 60 * 4)
		{
			m_resultFlg = true;
		}

		// クリア画像
		m_clearScaleMat = Math::Matrix::CreateScale(m_clearScale, m_clearScale, 0);
		m_clearTransMat = Math::Matrix::CreateTranslation(s_clear.m_pos.x, s_clear.m_pos.y, 0);
		s_clear.m_mat = m_clearScaleMat * m_clearTransMat;
	}
}

void C_Result::GameOver()
{
	if (m_gameOverFlg)
	{

		if (!m_scaleUpDownFlg)
		{
			m_gmOverScale += 0.01;
			if (m_gmOverScale >= 1.0f)
			{
				m_scaleUpDownFlg = true;
				m_gmOverScale = 1.0f;
			}
		}
		else
		{
			m_gmOverScale -= 0.01;
			if (m_gmOverScale < 0.6f)
			{
				m_gmOverScale = 0.6f;
				m_scaleUpDownFlg = false;
			}
		}
		m_scaleUpDownCnt++;

		if (m_scaleUpDownCnt > 60 * 4)
		{
			m_resultFlg = true;
		}

		// クリア画像
		m_gmOverScaleMat = Math::Matrix::CreateScale(m_gmOverScale, m_gmOverScale, 0);
		m_gmOverTransMat = Math::Matrix::CreateTranslation(s_gameOver.m_pos.x, s_gameOver.m_pos.y, 0);
		s_gameOver.m_mat = m_gmOverScaleMat * m_gmOverTransMat;
	}
}
