#pragma once
class C_Player;

class C_GameUI
{
public:

	struct S_UI
	{
		Math::Vector2 m_pos;
		Math::Matrix  m_mat;
	};


	C_GameUI() { Init(); }
	~C_GameUI() { Release(); }

	void Draw();
	void Draw2();
	void Update();
	
	void SetInstance(std::shared_ptr<C_Player>a_player) { m_player = a_player; }

private:

	std::shared_ptr<C_Player>m_player;

	void Init();
	void Release();


	KdTexture m_specialGaugeTex;//必殺ゲージ

	KdTexture m_backgroundTex;  //背景
	S_UI      s_background;

	KdTexture m_hudPanelTex;    //HUD
	S_UI      s_hudPanel;

	KdTexture m_starsTex;       //星
	S_UI      s_stars;          
	float     m_starAnimCnt;

	KdTexture m_hpIconTex;      //HP枠
	S_UI      s_hpIcon; 

	KdTexture m_coolTimeIconTex;//HP枠
	S_UI      s_coolTimeIcon;


	KdTexture m_hpBarTex;       //HP緑バー
	S_UI      s_hpBar;
	float     m_hpRate = 0;

	KdTexture m_coolTimeBarTex; //クールタイムバー
	S_UI      s_coolTimeBar;
	float     m_coolTimeRate = 0;

	float     m_maxWidth;
	float     m_baseX;

	KdTexture m_UiPanelTex;
	S_UI      s_UiPanel;


	KdTexture m_fireIconTex;
	S_UI      s_fireIcon;
	float     m_fireAlpha;

	KdTexture m_waterIconTex;
	S_UI      s_waterIcon;
	float     m_waterAlpha;

	KdTexture m_grassIconTex;
	S_UI      s_grassIcon;
	float     m_grassAlpha;

};