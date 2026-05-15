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

	// タイトル、リスタートボタン描画
	SHADER.m_spriteShader.SetMatrix(s_button.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_buttonTex, Math::Rectangle(0, 0, 730, 100), 1.0f);

	// スコア
	for (int i = 0; i < maxDigits; i++)
	{
		if(m_scoreDrawFlg[i])
		{
			SHADER.m_spriteShader.SetMatrix(m_numbersMat[i]);
			SHADER.m_spriteShader.DrawTex(&m_numbersTex, Math::Rectangle(50 * m_digits[i], 0, 50, 50), 1.0f);
		}
	}

	// ウィークキル数
	for (int i = 0; i < maxKillsDigits; i++)
	{
		if(m_weakKillsDrawFlg[i])
		{
			SHADER.m_spriteShader.SetMatrix(m_weakKillsMat[i]);
			SHADER.m_spriteShader.DrawTex(&m_numbersTex, Math::Rectangle(50 * m_weakKillsDigits[i], 0, 50, 50), 1.0f);
		}
	}
	// ノーマルキル数
	for (int i = 0; i < maxKillsDigits; i++)
	{
		if (m_normalKillsDrawFlg[i])
		{
			SHADER.m_spriteShader.SetMatrix(m_normalKillsMat[i]);
			SHADER.m_spriteShader.DrawTex(&m_numbersTex, Math::Rectangle(50 * m_normalKillsDigits[i], 0, 50, 50), 1.0f);
		}
		
	}
	// レジストキル数
	for (int i = 0; i < maxKillsDigits; i++)
	{
		if(m_resistKillsDrawFlg[i])
		{
			SHADER.m_spriteShader.SetMatrix(m_resistKillsMat[i]);
			SHADER.m_spriteShader.DrawTex(&m_numbersTex, Math::Rectangle(50 * m_resistKillsDigits[i], 0, 50, 50), 1.0f);
		}
	}
}

void C_Result::Update()
{

	GameClear();
	GameOver();

	//if (!m_resultFlg)return;

	Score();

	WeakKills();
	NormalKills();
	ResistKills();

	// タイトル、リザルトボタン
	s_button.m_mat = Math::Matrix::CreateTranslation(s_button.m_pos.x, s_button.m_pos.y, 0);

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
	s_uiPanel.m_pos = { 0,70 };

	m_clearTex.Load("Textures/Result/gameClear.png");
	s_clear.m_pos = { 0,100 };

	m_gameOverTex.Load("Textures/Result/gameOver.png");
	s_gameOver.m_pos = { 0,120 };

	m_buttonTex.Load("Textures/Result/button.png");
	s_button.m_pos = {0,-280};
	
	m_numbersTex.Load("Textures/Result/numbers.png");
	for (int i = 0; i < maxDigits; i++)
	{
		m_numbersPos[i].x = 40 + i * 40;
		m_numbersPos[i].y = -55;
		m_scoreDrawFlg[i] = true;
	}

	for (int i = 0; i < maxKillsDigits; i++)
	{
		m_weakKillsPos[i].x = 240 + i * 40;
		m_weakKillsPos[i].y = 150;

		m_normalKillsPos[i].x = 240 + i * 40;
		m_normalKillsPos[i].y = 80;

		m_resistKillsPos[i].x = 240 + i * 40;
		m_resistKillsPos[i].y = 10;
	}
}

void C_Result::Release()
{
	m_backgroundTex.Release();
	m_uiPanelTex.Release();
	m_clearTex.Release();
	m_gameOverTex.Release();
	m_buttonTex.Release();
	m_numbersTex.Release();
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

void C_Result::Score()
{

	// 配列に各桁の数値を格納
	unsigned long tmp = m_score;
	for (int i = maxDigits - 1; i >= 0; --i)
	{
		// 下位の桁から抽出し、配列に格納
		m_digits[i] = tmp % 10;// 余りを求める演算子 %
		tmp /= 10;
	}
	// スコアの表示、非表示処理
	for (int i = maxDigits - 1; i >= 0; --i)
	{

		if (i != maxDigits - 1)
		{

			for (int j = 0; j < i + 1; j++)
			{
				if (m_digits[i - j] >= 1)
				{
					m_scoreDrawFlg[i] = true;
					break;
				}
				else
				{
					m_scoreDrawFlg[i] = false;
				}
			}
		}

		// 右端の数字は必ず表示
		if (i == maxDigits - 1)
		{
			m_scoreDrawFlg[i] = true;
		}

	}

	for (int i = 0; i < maxDigits; i++)
	{
		m_numbersMat[i] = Math::Matrix::CreateTranslation(m_numbersPos[i].x, m_numbersPos[i].y, 0);
	}

}

void C_Result::WeakKills()
{
	// ウィークキル数
	int weakTmp = m_weakKillsCnt;
	for (int i = maxKillsDigits - 1; i >= 0; --i)
	{
		// 下位の桁から抽出し、配列に格納
		m_weakKillsDigits[i] = weakTmp % 10;// 余りを求める演算子 %
		weakTmp /= 10;
	}

	// キル数の表示、非表示処理
	for (int i = maxKillsDigits - 1; i >= 0; --i)
	{
		if (i != maxKillsDigits - 1)
		{
			for (int j = 0; j < i + 1; j++)
			{
				if (m_weakKillsDigits[i - j] >= 1)
				{
					m_weakKillsDrawFlg[i] = true;
					break;
				}
				else
				{
					m_weakKillsDrawFlg[i] = false;
				}
			}
		}
		// 右端の数字は必ず表示
		if (i == maxKillsDigits - 1)
		{
			m_weakKillsDrawFlg[i] = true;
		}
	}

	for (int i = 0; i < maxKillsDigits; i++)
	{
		m_weakKillsMat[i] = Math::Matrix::CreateTranslation(m_weakKillsPos[i].x, m_weakKillsPos[i].y, 0);
	}
}

void C_Result::NormalKills()
{
	// ノーマルキル数
	int normalTmp = m_normalKillsCnt;
	for (int i = maxKillsDigits - 1; i >= 0; --i)
	{
		// 下位の桁から抽出し、配列に格納
		m_normalKillsDigits[i] = normalTmp % 10;// 余りを求める演算子 %
		normalTmp /= 10;
	}

	// キル数の表示、非表示処理
	for (int i = maxKillsDigits - 1; i >= 0; --i)
	{
		if (i != maxKillsDigits - 1)
		{
			for (int j = 0; j < i + 1; j++)
			{
				if (m_normalKillsDigits[i - j] >= 1)
				{
					m_normalKillsDrawFlg[i] = true;
					break;
				}
				else
				{
					m_normalKillsDrawFlg[i] = false;
				}
			}
		}
		// 右端の数字は必ず表示
		if (i == maxKillsDigits - 1)
		{
			m_normalKillsDrawFlg[i] = true;
		}
	}

	for (int i = 0; i < maxKillsDigits; i++)
	{
		m_normalKillsMat[i] = Math::Matrix::CreateTranslation(m_normalKillsPos[i].x, m_normalKillsPos[i].y, 0);
	}
}

void C_Result::ResistKills()
{
	// レジストキル数
	int resistTmp = m_resistKillsCnt;
	for (int i = maxKillsDigits - 1; i >= 0; --i)
	{
		// 下位の桁から抽出し、配列に格納
		m_resistKillsDigits[i] = resistTmp % 10;// 余りを求める演算子 %
		resistTmp /= 10;
	}

	// キル数の表示、非表示処理
	for (int i = maxKillsDigits - 1; i >= 0; --i)
	{
		if (i != maxKillsDigits - 1)
		{
			for (int j = 0; j < i + 1; j++)
			{
				if (m_resistKillsDigits[i - j] >= 1)
				{
					m_resistKillsDrawFlg[i] = true;
					break;
				}
				else
				{
					m_resistKillsDrawFlg[i] = false;
				}
			}
		}
		// 右端の数字は必ず表示
		if (i == maxKillsDigits - 1)
		{
			m_resistKillsDrawFlg[i] = true;
		}
	}

	for (int i = 0; i < maxKillsDigits; i++)
	{
		m_resistKillsMat[i] = Math::Matrix::CreateTranslation(m_resistKillsPos[i].x, m_resistKillsPos[i].y, 0);
	}

}
