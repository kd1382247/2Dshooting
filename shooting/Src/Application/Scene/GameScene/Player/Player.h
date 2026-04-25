#pragma once
#include "Element.h"
class C_Bullet;


class C_Player
{

public:
	enum PlayerMotion
	{
		RightMove2 = 4,
		RightMove1 = 3,
		Idle = 2,
		LeftMove1 = 1,
		LeftMove2 = 0
	};


	struct S_Player
	{
		Math::Vector2 m_pos;
		Math::Vector2 m_move;
		Math::Matrix  m_transMat;
		Math::Matrix  m_rotationMat;
		Math::Matrix  m_mat;
		float         m_hp;
		bool          m_aliveFlg;
		bool          m_hitFlg;
		float         m_animCnt;
		float         m_angle;
		Element       m_nowElement;
	};

	struct S_Exhaust
	{
		Math::Vector2 m_pos;
		Math::Matrix  m_mat;
		Math::Matrix  m_transMat;
		Math::Matrix  m_rotationMat;
		bool          m_alive;
		float         m_animCnt;
		float         m_angle;
	};

	struct S_ChangeEffect
	{
		Math::Vector2 m_pos;
		Math::Matrix  m_mat;
		float         m_animCnt;
		float         m_alive;
	};

	struct S_Chara
	{
		Math::Vector2 m_pos;
		Math::Matrix  m_mat;
	};

public:

	C_Player() { Init(); }
	~C_Player() { Release(); }

	void Draw();
	void Update();
	
	
	float GetAnimCnt() { return s_exhaust.m_animCnt; }

private:

	std::shared_ptr<C_Bullet>m_bullet;

	//解放処理
	void Init();
	void Release();

	//弾発射関数
	void Shoot();

	//プレイヤーの関数
	void DrawPlayer();
	void UpdatePlayer();
	void InitPlayer();

	void ElementChange();

	//排気エフェクト
	void DrawExhaust();
	void UpdateExhaust();
	void InitExhaust();

	//属性切り替えエフェクト
	void DrawChangeEffect();
	void UpdateChangeEffect();
	void InitChangeEffect();


	KdTexture     m_playerTex;
	S_Player      s_player;

	KdTexture     m_exhaustTex;
	S_Exhaust       s_exhaust;

	KdTexture     m_changeEffectTex;
	S_ChangeEffect  s_changeEffect;

	KdTexture     m_charaTex;
	S_Chara       s_chara;

	PlayerMotion  e_playerMotion;
	
	float         m_rightMoveCnt;
	float         m_leftMoveCnt;
	bool          m_rightMoveFlg;
	bool          m_leftMoveFlg;
	const int     m_moveSpeed=5;


	bool          m_keyFlg;

};