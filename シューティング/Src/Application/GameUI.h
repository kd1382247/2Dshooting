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
	
	KdTexture m_backgroundTex;  //背景
	KdTexture m_hpBarTex;       //HPバー
	KdTexture m_specialGaugeTex;//必殺ゲージ

	S_UI s_background;

};