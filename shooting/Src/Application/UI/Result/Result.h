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

	bool GetResultFlg()             { return m_resultFlg; }

private:

	void Init();
	void Release();

	void GameClear();
	void GameOver();

	KdTexture m_backgroundTex;
	S_Result  s_background;

	KdTexture m_uiPanelTex;
	S_Result  s_uiPanel = {};

	KdTexture m_titleBarTex;
	S_Result  s_titleBar = {};

	KdTexture m_restartBarTex;
	S_Result  s_restartBar = {};


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
};