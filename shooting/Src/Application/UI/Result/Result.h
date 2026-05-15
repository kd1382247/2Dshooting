#pragma once

class C_Result
{
public:

	struct S_Result
	{
		Math::Vector2 m_pos;
		Math::Matrix  m_mat;
	};

	C_Result() { Init(); }
	~C_Result() { Release(); }


	void Draw();
	void Update();


	void SetClearFlg(bool a_flg)    { m_gameClearFlg = a_flg; }
	void SetGameOverFlg(bool a_flg) { m_gameOverFlg = a_flg; }

	void SetKillsCnt(int a_weakCnt, int a_normalCnt, int a_resist)
	{
		m_weakKillsCnt = a_weakCnt;
		m_normalKillsCnt = a_normalCnt;
		m_resistKillsCnt = a_resist;
	}

	bool GetResultFlg()             { return m_resultFlg; }

	void SetScore(float a_score)    { m_score = a_score; }

private:

	void Init();
	void Release();

	void GameClear();
	void GameOver();

	void Score();

	void WeakKills();
	void NormalKills();
	void ResistKills();

	KdTexture m_backgroundTex;
	S_Result  s_background;

	KdTexture m_uiPanelTex;
	S_Result  s_uiPanel = {};

	KdTexture m_buttonTex;
	S_Result  s_button = {};


	KdTexture    m_clearTex;
	S_Result     s_clear = {};
	Math::Matrix m_clearScaleMat;
	Math::Matrix m_clearTransMat;
	float        m_clearScale=0.0f;


	KdTexture    m_gameOverTex;
	S_Result     s_gameOver = {};
	Math::Matrix m_gmOverScaleMat;
	Math::Matrix m_gmOverTransMat;
	float        m_gmOverScale=0.0f;

	float         m_scaleUpDownCnt = {};
	bool          m_scaleUpDownFlg = {};
	

	// ゲームクリアフラグ
	bool            m_gameClearFlg = {};
	bool            m_gameOverFlg = {};
	bool            m_resultFlg = {};


	unsigned long     m_score = 0;
	static const int  maxDigits = 7;
	int               m_digits[maxDigits] = {}; // 各桁の数値を格納
	bool              m_scoreDrawFlg[maxDigits] = {};

	static const int maxKillsDigits = 2;

	float            m_weakKillsCnt = {};
	int              m_weakKillsDigits[maxKillsDigits] = {};
	Math::Vector2    m_weakKillsPos[maxKillsDigits] = {};
	Math::Matrix     m_weakKillsMat[maxKillsDigits] = {};
	bool             m_weakKillsDrawFlg[maxKillsDigits] = {};  // ウィークキル数の桁数描画フラグ

	float            m_normalKillsCnt = {};
	int              m_normalKillsDigits[maxKillsDigits] = {};
	Math::Vector2    m_normalKillsPos[maxKillsDigits] = {};
	Math::Matrix     m_normalKillsMat[maxKillsDigits] = {};
	bool             m_normalKillsDrawFlg[maxKillsDigits] = {};  // ノーマルキル数の桁数描画フラグ

	float            m_resistKillsCnt = {};
	int              m_resistKillsDigits[maxKillsDigits] = {};
	Math::Vector2    m_resistKillsPos[maxKillsDigits] = {};
	Math::Matrix     m_resistKillsMat[maxKillsDigits] = {};
	bool             m_resistKillsDrawFlg[maxKillsDigits] = {};  // ウィークキル数の桁数描画フラグ


	KdTexture     m_numbersTex;
	Math::Matrix  m_numbersMat[maxDigits];
	Math::Vector2 m_numbersPos[maxDigits] = {};





};