#pragma once

struct S_Title
{
	Math::Vector2 m_pos;
	Math::Matrix  m_mat;
};

class C_Title
{
public:

	C_Title() { Init(); }
	~C_Title() { Release(); }

	void Draw();
	void Update();
	
private:

	void Init();
	void Release();

	KdTexture     m_titleTex;
	S_Title       s_title;
	KdTexture     m_pressEnterTex;
	S_Title       s_pressEnter;

	float         m_alpha;
	float         m_delta;

};