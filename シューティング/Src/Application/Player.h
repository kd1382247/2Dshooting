#pragma once

enum PlayerMotion
{
	RightMove2 = 4,
	RightMove1 = 3,
	Idle       = 2,
	LeftMove1  = 1,
	LeftMove2  = 0
};

enum NowElement
{
	Fire,
	Grass,
	Water
};
struct S_Player
{
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Matrix  m_scaleMat;
	Math::Matrix  m_transMat;
	Math::Matrix  m_rotationMat;
	Math::Matrix  m_mat;
	Math::Vector2 m_scale;
	float         m_hp;
	bool          m_alive;
	bool          m_hitFlg;
	float         m_animCnt;
	float         m_angle;
};

struct Exhaust
{
	Math::Vector2 m_pos;
	Math::Matrix  m_mat;
	Math::Matrix  m_transMat;
	Math::Matrix  m_rotationMat;
	bool          m_alive;
	float         m_animCnt;
	float         m_angle;
};

class C_Player
{
public:

	C_Player();
	~C_Player();

	void Draw();
	void Update();
	void Init();
	void Release();


	float GetAnimCnt() { return s_exhaust.m_animCnt; }
private:

	NowElement    e_nowElement;

	KdTexture     m_player_r_Tex;
	KdTexture     m_player_g_Tex;
	KdTexture     m_player_b_Tex;
	S_Player      s_player;

	KdTexture     m_exhaustTex;
	Exhaust       s_exhaust;

	PlayerMotion  e_playerMotion;
	
	float         m_rightMoveCnt;
	float         m_leftMoveCnt;
	bool          m_rightMoveFlg;
	bool          m_leftMoveFlg;
	const int     m_moveSpeed=5;


};