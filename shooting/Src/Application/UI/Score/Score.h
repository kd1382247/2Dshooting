#pragma once

class C_Score
{
public:

	C_Score() { Init(); }
	~C_Score() { Release(); }



	void Draw();
	void Update();

	void ScoreCntUp(float a_score)
	{
		m_score += a_score;
		if (m_score > 9999999999)
		{
			m_score = 9999999999;
		}
	}

private:

	void Init();
	void Release();

	unsigned long     m_score = 0;
	static const int  maxDigits = 7;
	int               m_digits[maxDigits] = {}; // 各桁の数値を格納

	KdTexture     m_numbersTex;
	Math::Matrix  m_numbersMat[maxDigits];
	Math::Vector2 m_numbersPos[maxDigits] = {};

	KdTexture     m_scoreTex;
	Math::Matrix  m_scoreTexMat;
	Math::Vector2 m_scoreTexPos = {};

	


};
