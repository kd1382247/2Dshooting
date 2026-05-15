#include "Score.h"
#include"../Result/Result.h"

void C_Score::Draw()
{
	for (int i = 0; i < maxDigits; i++)
	{
		if(m_numbersDrawFlg[i])
		{
			SHADER.m_spriteShader.SetMatrix(m_numbersMat[i]);
			SHADER.m_spriteShader.DrawTex(&m_numbersTex, Math::Rectangle(70 * m_digits[i], 0, 70, 70), 1.0f);
		}
	}

	SHADER.m_spriteShader.SetMatrix(m_scoreTexMat);
	SHADER.m_spriteShader.DrawTex(&m_scoreTex, Math::Rectangle(0, 0, 224, 80), 1.0f);
}

void C_Score::Update()
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
					m_numbersDrawFlg[i] = true;
					break;
				}
				else
				{
					m_numbersDrawFlg[i] = false;
				}
			}
		}

		// 右端の数字は必ず表示
		if (i == maxDigits - 1)
		{
			m_numbersDrawFlg[i] = true;
		}
	}

	for (int i = 0; i < maxDigits; i++)
	{
		m_numbersMat[i] = Math::Matrix::CreateTranslation(m_numbersPos[i].x, m_numbersPos[i].y, 0);
	}

	m_scoreTexMat = Math::Matrix::CreateTranslation(m_scoreTexPos.x, m_scoreTexPos.y, 0);

	m_result->SetScore(m_score);
	m_result->SetKillsCnt(m_weakKillCnt,m_normalKillCnt,m_resistKillCnt);
	
}

void C_Score::KillsCntUp(MatchupType a_matchupType)
{
	if (a_matchupType == WEAK)
	{
		m_weakKillCnt++;
	}
	if (a_matchupType == NORMAL)
	{
		m_normalKillCnt++;
	}
	if (a_matchupType == RESIST)
	{
		m_resistKillCnt++;
	}
}

void C_Score::Init()
{
	m_numbersTex.Load("Textures/UI/numbers.png");
	for (int i = 0; i < maxDigits; i++)
	{
		m_numbersPos[i].x =280+i*50;
		m_numbersPos[i].y = -310;
		m_numbersDrawFlg[i] = true;
	}

	m_scoreTex.Load("Textures/UI/score.png");
	m_scoreTexPos = { 140,-315 };
}

void C_Score::Release()
{
	m_numbersTex.Release();
}
