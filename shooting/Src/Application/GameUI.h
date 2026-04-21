#pragma once

struct S_UI
{
	Math::Vector2 m_pos;
	Math::Matrix  m_mat;
};

class C_GameUI
{
public:

	C_GameUI();
	~C_GameUI();

	void Draw();
	void Init();
	void Update();
	void Release();


private:

	KdTexture m_specialGaugeTex;//必殺ゲージ

	KdTexture m_backgroundTex;  //背景
	S_UI      s_background;

	KdTexture m_hpIconTex;      //HP枠
	S_UI      s_hpIcon; 

	KdTexture m_hpBar_r_Tex;    //HP赤バー
	S_UI      s_hpBar_r;

	KdTexture m_hpBar_g_Tex;    //HP緑バー
	S_UI      s_hpBar_g;

	KdTexture m_UiPanelTex;
	S_UI      s_UiPanel;

	KdTexture m_playerIconTex;
	S_UI      s_playerIcon;

};